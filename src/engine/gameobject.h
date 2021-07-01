#ifndef _SGE_GAMEOBJECT_H
#define _SGE_GAMEOBJECT_H

#include "camera.h"
#include "gamecomponent.h"
#include "input.h"
#include "transform.h"
#include "shader.h"

#include <memory>
#include <vector>

namespace SGE {
class GameObject {
    private:
        Math::Transform transform_{};
        std::vector<std::shared_ptr<GameObject>> children_{};
        std::vector<std::shared_ptr<GameComponent>> components_{};

    public:
        virtual void input(const Input& input);
        virtual void update();
        virtual void render(Shader& shader, const Camera& camera);

        void add_child(std::shared_ptr<GameObject> child);
        void add_component(std::shared_ptr<GameComponent> component);

        void set_transform(const Math::Transform& transform);
        Math::Transform& transform();
};
} // namespace SGE
#endif
