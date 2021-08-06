#ifndef _SGE_CPP_SCRIPT_COMPONENT_H
#define _SGE_CPP_SCRIPT_COMPONENT_H

#include "engine/ecs/scriptable.h"

namespace SGE
{

class CPPScriptComponent
{
  public:
    Scriptable* instance = nullptr;

    Scriptable* (*instantiate_script)()         = nullptr;
    void (*destroy_script)(CPPScriptComponent*) = nullptr;

    template <typename T>
    void bind()
    {
        instantiate_script = []() { return static_cast<Scriptable*>(new T()); };

        destroy_script = [](CPPScriptComponent* script) {
            delete script->instance;
            script->instance = nullptr;
        };
    }
};

} // namespace SGE

#endif
