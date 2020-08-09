#ifndef _SGE_DOOR_H
#define _SGE_DOOR_H

#include "basicshader.h"
#include "material.h"
#include "mesh.h"
#include "transform.h"
#include "vector2.h"
#include "vector3.h"

#include <chrono>

namespace Game {
class Door {
    private:
        Math::Transform transform_;
        Material material_;

        static inline Mesh mesh;
        static inline bool mesh_created = false;

        bool is_opening_ = false;

        Math::Vector3 open_position_;
        Math::Vector3 close_position_;

        std::chrono::time_point<std::chrono::steady_clock> open_start_time_;
        std::chrono::time_point<std::chrono::steady_clock> open_time_;
        std::chrono::time_point<std::chrono::steady_clock> closing_start_time_;
        std::chrono::time_point<std::chrono::steady_clock> close_time_;

        Math::Vector3 interpolate_lerp(const Math::Vector3& start, const Math::Vector3& end, float factor);

    public:
        Door() = default;
        explicit Door(const Math::Transform& transform, const Material& material, const Math::Vector3& open_position);
        void update();
        void render(BasicShader& shader);
        Math::Transform& transform();

        static inline const float LENGTH = 1.0F;
        static inline const float HEIGHT = 1.0F;
        static inline const float WIDTH = 0.125F;
        static inline const float START = 0.0F;

        Math::Vector2 size() const;

        std::chrono::milliseconds DOOR_OPEN_TIME_ = std::chrono::seconds{1};
        std::chrono::milliseconds DOOR_CLOSE_DELAY_ = std::chrono::seconds{2};

        void open();
};
} // namespace Game
#endif
