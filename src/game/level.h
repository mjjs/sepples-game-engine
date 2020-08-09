#ifndef _SGE_LEVEL_H
#define _SGE_LEVEL_H

#include "basicshader.h"
#include "bitmap.h"
#include "door.h"
#include "enemy.h"
#include "input.h"
#include "material.h"
#include "mesh.h"
#include "transform.h"
#include "vector2.h"
#include "vector3.h"
#include "vertex.h"

#include <string>
#include <vector>

namespace Game {
class Level {
    private:
        const float SPOT_WIDTH_ = 1;
        const float SPOT_LENGTH_ = 1;
        const float SPOT_HEIGHT_ = 1;

        const int NUM_TEX_EXP_ = 4;
        const int NUM_TEXTURES_ = NUM_TEX_EXP_ * NUM_TEX_EXP_;

        Bitmap map_;
        Mesh mesh_;
        Math::Transform transform_;
        BasicShader shader_;
        Material material_;

        // TEMP

        void generate_map(const Material& material);
        void add_face(std::vector<int>& indices, int start, bool flip) const;
        void add_vertices(std::vector<Vertex>& vertices, int i, int j, bool x, bool y, bool z, float offset, const std::vector<float>& texture_coordinates) const;
        std::vector<float> calculate_texture_coordinates(int colour) const;

        Math::Vector2 rectangle_collide(const Math::Vector2& old_position, const Math::Vector2& new_position,
                const Math::Vector2& size1, const Math::Vector2& size2, const Math::Vector2& pos2);

        void add_special(int blue_value, int x, int y);
        void add_door(int x, int y);

        std::vector<Door> doors_;
        std::vector<Enemy> enemies_;

    public:
        explicit Level(const std::string& level_path, const std::string& texture_path);
        void input(const Input& inputs);
        void update();
        void render();
        void open_doors(const Math::Vector3& position);
        Math::Transform& transform();
        std::vector<Enemy>& enemies();
        Math::Vector3 check_collision(const Math::Vector3& old_position, const Math::Vector3& new_position,
                float width, float length);
};
} // namespace Game
#endif
