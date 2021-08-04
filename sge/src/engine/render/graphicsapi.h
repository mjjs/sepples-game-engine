#ifndef _SGE_GRAPHICSAPI_H
#define _SGE_GRAPHICSAPI_H

#include "vector3.h"
#include <memory>

namespace SGE {

class GraphicsAPI {
    public:
        enum class VENDOR {
            OPENGL, VULKAN,
        };

    private:
        // NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
        static VENDOR vendor_;

    public:
        GraphicsAPI() = default;
        virtual ~GraphicsAPI() = default;

        GraphicsAPI(const GraphicsAPI&) = delete;
        GraphicsAPI(const GraphicsAPI&&) = delete;
        GraphicsAPI& operator=(const GraphicsAPI&) = delete;
        GraphicsAPI& operator=(const GraphicsAPI&&) = delete;

        static std::unique_ptr<GraphicsAPI> create();
        static VENDOR vendor();

        virtual void clear_screen() = 0;
        virtual void set_clear_colour(const Vector3& colour) = 0;
};

} // namespace SGE

#endif