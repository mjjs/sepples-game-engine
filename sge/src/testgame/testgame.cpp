#include "sge.h"

#include <cstdint>
#include <memory>
#include <vector>

class CameraScript : public SGE::Scriptable
{
  private:
    const float camera_move_speed_   = 25;
    const float camera_rotate_speed_ = 90;

  public:
    void update(const float delta) override
    {
        auto& camera = get_component<SGE::CameraComponent>().camera();

        if (SGE::Input::is_key_down(SDLK_w)) {
            camera.move(camera.transform().rotation().get_forward(),
                        camera_move_speed_ * delta);
        }

        if (SGE::Input::is_key_down(SDLK_s)) {
            camera.move(camera.transform().rotation().get_back(),
                        camera_move_speed_ * delta);
        }

        if (SGE::Input::is_key_down(SDLK_a)) {
            camera.move(camera.transform().rotation().get_left(),
                        camera_move_speed_ * delta);
        }

        if (SGE::Input::is_key_down(SDLK_d)) {
            camera.move(camera.transform().rotation().get_right(),
                        camera_move_speed_ * delta);
        }

        if (SGE::Input::is_key_down(SDLK_UP)) {
            camera.rotate_x(camera_rotate_speed_ * delta);
        }

        if (SGE::Input::is_key_down(SDLK_DOWN)) {
            camera.rotate_x(-camera_rotate_speed_ * delta);
        }

        if (SGE::Input::is_key_down(SDLK_LEFT)) {
            camera.rotate_y(camera_rotate_speed_ * delta);
        }

        if (SGE::Input::is_key_down(SDLK_RIGHT)) {
            camera.rotate_y(-camera_rotate_speed_ * delta);
        }
    }

    void fixed_update() override
    {
    }
};

class TestGame : public SGE::Game
{
  private:
    std::unique_ptr<SGE::Scene> current_scene_;

    std::shared_ptr<SGE::Shader> basic_shader_;
    std::shared_ptr<SGE::Mesh> floor_;
    std::shared_ptr<SGE::Model> backpack_;

  public:
    TestGame() : current_scene_(std::make_unique<SGE::Scene>())
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

        auto camera = current_scene_->add_game_object("camera");
        camera.add_component<SGE::CameraComponent>();
        camera.add_component<SGE::CPPScriptComponent>().bind<CameraScript>();
    }

    void update(float delta) override
    {
        current_scene_->update(delta);
    }

    void fixed_update() override
    {
        current_scene_->fixed_update();
    }
};

std::unique_ptr<SGE::Game> SGE::CreateGame([[maybe_unused]] int argc,
                                           [[maybe_unused]] char** argv)
{
    return std::make_unique<TestGame>();
}
