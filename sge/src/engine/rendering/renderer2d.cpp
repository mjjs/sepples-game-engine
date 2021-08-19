#include "engine/rendering/renderer2d.h"

#include "engine/core/transform.h"
#include "engine/rendering/buffers/bufferlayout.h"
#include "engine/rendering/buffers/indexbuffer.h"
#include "engine/rendering/buffers/uniformbuffer.h"
#include "engine/rendering/buffers/vertexarray.h"
#include "engine/rendering/buffers/vertexbuffer.h"
#include "engine/rendering/camera.h"
#include "engine/rendering/shader.h"
#include "engine/rendering/texture.h"
#include "engine/rendering/texture2d.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace SGE
{

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
std::unique_ptr<GraphicsAPI> Renderer2D::graphics_api_ = GraphicsAPI::create();

struct QuadVertex {
    glm::vec3 position{};
    glm::vec4 colour{};
    glm::vec2 texture_coordinate{};
    float texture_index{0};
};

static constexpr std::size_t BATCH_SIZE        = 1000;
static constexpr std::size_t INDICES_PER_QUAD  = 6;
static constexpr std::size_t MAX_INDICES       = BATCH_SIZE * INDICES_PER_QUAD;
static constexpr std::size_t MAX_TEXTURE_SLOTS = 32;

static constexpr std::array<glm::vec4, 4> DEFAULT_VERTEX_POSITIONS{
    glm::vec4{-0.5F, 0.5F, 0.0F, 1.0F},
    glm::vec4{0.5F, 0.5F, 0.0F, 1.0F},
    glm::vec4{-0.5F, -0.5F, 0.0F, 1.0F},
    glm::vec4{0.5F, -0.5F, 0.0F, 1.0F},
};

static constexpr std::array<glm::vec2, 4> TEXTURE_COORDINATES{
    glm::vec2{0.0F, 0.0F},
    glm::vec2{0.0F, 1.0F},
    glm::vec2{1.0F, 0.0F},
    glm::vec2{1.0F, 1.0F},
};

struct RendererData {
    std::shared_ptr<UniformBuffer> camera_buffer = nullptr;
    std::shared_ptr<VertexBuffer> vertex_buffer  = nullptr;
    std::shared_ptr<VertexArray> vertex_array    = nullptr;
    std::shared_ptr<Shader> quad_shader          = nullptr;
    std::array<std::shared_ptr<Texture>, MAX_TEXTURE_SLOTS> textures;

    std::size_t buffered_quad_count = 0;
    std::size_t indices_to_draw     = 0;
    std::size_t texture_slot_index  = 1;
    std::array<QuadVertex, BATCH_SIZE> quads{};
} static renderer_state; // NOLINT

void Renderer2D::init()
{
    renderer_state.quad_shader = Shader::create("res/shaders/basic_2d");
    renderer_state.quad_shader->bind();

    std::vector<int> texture_samplers(MAX_TEXTURE_SLOTS);
    for (std::size_t i = 0; i < MAX_TEXTURE_SLOTS; ++i) {
        texture_samplers[i] = i;
    }

    renderer_state.quad_shader->set_uniform("textures_u", texture_samplers);

    auto white_texture = Texture2D::create({1.0F, 1.0F, 1.0F, 1.0F}, 1, 1);
    renderer_state.textures[0] = white_texture;

    renderer_state.camera_buffer = UniformBuffer::create(sizeof(glm::mat4), 1);

    renderer_state.vertex_buffer =
        VertexBuffer::create(BATCH_SIZE * sizeof(QuadVertex));
    renderer_state.vertex_buffer->set_layout({
        {ShaderDataType::VEC3, "u_position"},
        {ShaderDataType::VEC4, "u_colour"},
        {ShaderDataType::VEC2, "u_texture_coordinate"},
        {ShaderDataType::FLOAT, "u_texture_index"},
    });

    std::vector<std::uint32_t> indices(MAX_INDICES);

    std::size_t offset = 0;
    for (std::size_t i = 0; i < MAX_INDICES; i += INDICES_PER_QUAD) {
        indices[i]     = offset;
        indices[i + 1] = offset + 2;
        indices[i + 2] = offset + 1;
        indices[i + 3] = offset + 2;
        indices[i + 4] = offset + 3;
        indices[i + 5] = offset + 1;

        offset += 4;
    }

    renderer_state.vertex_array = VertexArray::create();
    renderer_state.vertex_array->add_vertex_buffer(
        renderer_state.vertex_buffer);
    renderer_state.vertex_array->set_index_buffer(IndexBuffer::create(indices));
}

void Renderer2D::prepare_frame(const Camera& camera)
{
    auto proj = camera.get_view_projection();
    renderer_state.camera_buffer->set_data(&proj, sizeof(glm::mat4));
    initialize_batch();
}

void Renderer2D::end_frame()
{
    execute_batch();
}

void Renderer2D::execute_batch()
{
    if (renderer_state.buffered_quad_count == 0) {
        return;
    }

    std::size_t data_size =
        renderer_state.buffered_quad_count * sizeof(QuadVertex);
    renderer_state.vertex_buffer->set_data(renderer_state.quads.data(),
                                           data_size);

    for (std::size_t i = 0; i < renderer_state.texture_slot_index; ++i) {
        renderer_state.textures[i]->bind(i); // NOLINT
    }

    renderer_state.quad_shader->bind();

    renderer_state.vertex_array->bind();

    graphics_api_->draw_indexed(renderer_state.vertex_array);
}

void Renderer2D::initialize_batch()
{
    renderer_state.indices_to_draw     = 0;
    renderer_state.buffered_quad_count = 0;
    renderer_state.texture_slot_index  = 1;
}

void Renderer2D::end_batch()
{
    execute_batch();
    initialize_batch();
}

void Renderer2D::draw_quad(const Transform& transform, const glm::vec4& colour)
{
    draw_quad(transform, colour, nullptr);
}

void Renderer2D::draw_quad(const Transform& transform,
                           const std::shared_ptr<Texture>& texture)
{
    draw_quad(transform, glm::vec4{1.0F}, texture);
}

void Renderer2D::draw_quad(const Transform& transform, const glm::vec4& colour,
                           const std::shared_ptr<Texture>& texture)
{
    if (renderer_state.indices_to_draw >= MAX_INDICES ||
        renderer_state.texture_slot_index >= MAX_TEXTURE_SLOTS) {
        end_batch();
    }

    float texture_slot = 0.0F;

    if (texture) {
        bool stored = false;

        for (std::size_t i = 0; i < renderer_state.texture_slot_index; ++i) {
            const auto& tex = renderer_state.textures[i]; // NOLINT

            if (*tex == *texture) {
                stored       = true;
                texture_slot = (float)i;
                break;
            }
        }

        if (!stored) {
            renderer_state // NOLINT
                .textures[renderer_state.texture_slot_index] = texture;
            texture_slot = (float)renderer_state.texture_slot_index;
            ++renderer_state.texture_slot_index;
        }
    }

    for (std::size_t i = 0; i < 4; ++i) {
        auto& vertex =
            renderer_state.quads[renderer_state.buffered_quad_count]; // NOLINT

        vertex.position = transform.get_transformation() *
                          DEFAULT_VERTEX_POSITIONS[i]; // NOLINT
        vertex.colour             = colour;
        vertex.texture_coordinate = TEXTURE_COORDINATES[i]; // NOLINT
        vertex.texture_index      = texture_slot;
        ++renderer_state.buffered_quad_count;
    }

    renderer_state.indices_to_draw += INDICES_PER_QUAD;
}

} // namespace SGE
