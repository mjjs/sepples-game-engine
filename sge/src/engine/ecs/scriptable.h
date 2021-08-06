#ifndef _SGE_SCRIPTABLE_H
#define _SGE_SCRIPTABLE_H

#include "engine/ecs/gameobject.h"

namespace SGE
{

class Scene;

class Scriptable
{
    friend class Scene;

  private:
    GameObject game_object_;

  public:
    Scriptable()          = default;
    virtual ~Scriptable() = default;

    Scriptable(const Scriptable&)  = delete;
    Scriptable(const Scriptable&&) = delete;
    Scriptable& operator=(const Scriptable&) = delete;
    Scriptable& operator=(const Scriptable&&) = delete;

    virtual void on_create(){};
    virtual void on_destroy(){};
    virtual void update([[maybe_unused]] float delta){};

    template <typename ComponentType>
    ComponentType& get_component()
    {
        return game_object_.get_component<ComponentType>();
    }
};

} // namespace SGE

#endif
