#ifndef _SGE_LEVEL_H
#define _SGE_LEVEL_H

#include "basicshader.h"
#include "bitmap.h"
#include "door.h"
#include "enemy.h"
#include "input.h"
#include "material.h"
#include "medkit.h"
#include "mesh.h"
#include "player.h"
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

        int current_level_ = 0;

        Bitmap map_;
        Mesh mesh_;
        Math::Transform transform_;
        Material material_;

        Player player_;

        std::vector<Math::Vector2> collision_position_start_{};
        std::vector<Math::Vector2> collision_position_end_{};

        void generate_map(const Material& material);
        void add_face(std::vector<int>& indices, int start, bool flip) const;
        void add_vertices(std::vector<Vertex>& vertices, int i, int j, bool x, bool y, bool z, float offset, const std::vector<float>& texture_coordinates) const;
        std::vector<float> calculate_texture_coordinates(int colour) const;

        Math::Vector2 rectangle_collide(const Math::Vector2& old_position, const Math::Vector2& new_position,
                const Math::Vector2& size1, const Math::Vector2& size2, const Math::Vector2& pos2);

        void add_special(int blue_value, int x, int y);
        void add_door(int x, int y);

        Math::Vector2 line_intersect(const Math::Vector2& start_1, const Math::Vector2& end_1,
                const Math::Vector2& start_2, const Math::Vector2& end_2, bool& hit);

        std::vector<Door> doors_;
        std::vector<Enemy> enemies_;
        std::vector<Medkit> medkits_;
        std::vector<Math::Vector3> exits_;

        void next_level();

    public:
        explicit Level();
        void input(const Input& inputs);
        void update();
        void render(BasicShader& shader);
        void open_doors(const Math::Vector3& position, bool exit);
        Math::Transform& transform();
        std::vector<Enemy>& enemies();
        Math::Vector3 check_collision(const Math::Vector3& old_position, const Math::Vector3& new_position,
                float width, float length);
        Math::Vector2 check_intersection(const Math::Vector2& start, const Math::Vector2& end, bool& hit, bool hurt_monsters);

        Math::Vector2 line_intersect_rectangle(const Math::Vector2& line_start, const Math::Vector2& line_end,
                const Math::Vector2& rect_pos, const Math::Vector2& rect_size, bool& hit);

        void damage_player(int amount);
        Player& player();
};
} // namespace Game
#endif
