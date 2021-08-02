#ifndef _SGE_GRAPHICSAPI_H
#define _SGE_GRAPHICSAPI_H

#include "vector3.h"
#include <memory>

namespace SGE {

enum class API {
    OPENGL, VULKAN,
};

class GraphicsAPI {
    private:
        // NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
        static API api_;

    public:
        GraphicsAPI() = default;
        virtual ~GraphicsAPI() = default;

        GraphicsAPI(const GraphicsAPI&) = delete;
        GraphicsAPI(const GraphicsAPI&&) = delete;
        GraphicsAPI& operator=(const GraphicsAPI&) = delete;
        GraphicsAPI& operator=(const GraphicsAPI&&) = delete;

        static std::unique_ptr<GraphicsAPI> create();

        virtual void clear_screen() = 0;
        virtual void set_clear_colour(const Vector3& colour) = 0;
};

} // namespace SGE

#endif
