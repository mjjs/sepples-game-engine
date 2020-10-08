#ifndef _SGE_GAMEOBJECT_H
#define _SGE_GAMEOBJECT_H

#include "gamecomponent.h"
#include "transform.h"

#include <memory>
#include <vector>

namespace SGE {
class GameObject {
    private:
        Math::Transform transform_{};
        std::vector<std::shared_ptr<GameObject>> children_{};
        std::vector<std::shared_ptr<GameComponent>> components_{};

    public:
        virtual void input();
        virtual void update();
        virtual void render();

        void add_child(std::shared_ptr<GameObject> child);
        void add_component(std::shared_ptr<GameComponent> component);

        void set_transform(const Math::Transform& transform);
        Math::Transform& transform();
};
} // namespace SGE
#endif
