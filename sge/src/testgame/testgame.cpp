#include "sge.h"

#include <cstdint>
#include <memory>
#include <vector>

class TestGame : public SGE::Game
{
  private:
    std::unique_ptr<SGE::Scene> current_scene_;
    SGE::Camera camera_;

    std::shared_ptr<SGE::Shader> basic_shader_;
    std::shared_ptr<SGE::Mesh> floor_;
    std::shared_ptr<SGE::Model> backpack_;

  public:
    TestGame()
        : current_scene_(std::make_unique<SGE::Scene>()),
          camera_{70, (float)1270 / (float)800, .1, 1000}
    {
        auto backpack = current_scene_->add_game_object("backpack");
        backpack.add_component<SGE::ModelRendererComponent>(
            std::make_shared<SGE::Model>("res/models/backpack.obj"));

        auto floor = current_scene_->add_game_object("floor");

        std::vector<SGE::Vertex> floor_vertices{
            {{-10, -2, -10}, {0, 1, 0}, {0, 0}},
            {{-10, -2, 30}, {0, 1, 0}, {0, 1}},
            {{30, -2, -10}, {0, 1, 0}, {1, 0}},
            {{30, -2, 30}, {0, 1, 0}, {1, 1}},
        };

        std::vector<std::uint32_t> floor_indices = {0, 1, 2, 2, 1, 3};

        auto red_texture =
            SGE::Texture2D::create(SGE::Vector3{.8, .2, .3}, 1, 1);

        auto floor_mesh = std::make_shared<SGE::Mesh>(
            floor_vertices, floor_indices,
            SGE::Material{red_texture, nullptr, nullptr});

        floor.add_component<SGE::MeshRendererComponent>(floor_mesh);
    }

    void update(float delta) override
    {
        const float move_speed   = 25;
        const float rotate_speed = 90;

        if (SGE::Input::is_key_down(SDLK_w)) {
            camera_.move(camera_.transform().rotation().get_forward(),
                         move_speed * delta);
        }

        if (SGE::Input::is_key_down(SDLK_s)) {
            camera_.move(camera_.transform().rotation().get_back(),
                         move_speed * delta);
        }

        if (SGE::Input::is_key_down(SDLK_a)) {
            camera_.move(camera_.transform().rotation().get_left(),
                         move_speed * delta);
        }

        if (SGE::Input::is_key_down(SDLK_d)) {
            camera_.move(camera_.transform().rotation().get_right(),
                         move_speed * delta);
        }

        if (SGE::Input::is_key_down(SDLK_UP)) {
            camera_.rotate_x(rotate_speed * delta);
        }

        if (SGE::Input::is_key_down(SDLK_DOWN)) {
            camera_.rotate_x(-rotate_speed * delta);
        }

        if (SGE::Input::is_key_down(SDLK_LEFT)) {
            camera_.rotate_y(rotate_speed * delta);
        }

        if (SGE::Input::is_key_down(SDLK_RIGHT)) {
            camera_.rotate_y(-rotate_speed * delta);
        }

        SGE::RenderingEngine::prepare_frame(camera_);
        current_scene_->update(delta);
    }

    void fixed_update() override
    {
    }
};

std::unique_ptr<SGE::Game> SGE::CreateGame([[maybe_unused]] int argc,
                                           [[maybe_unused]] char** argv)
{
    return std::make_unique<TestGame>();
}
