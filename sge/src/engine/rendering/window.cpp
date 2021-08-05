#include "platform/linux/linuxwindow.h"
#include "engine/rendering/window.h"

#include <cstdint>
#include <memory>
#include <string>

namespace SGE {

std::unique_ptr<Window> Window::create(
        const std::string& title,
        std::uint32_t width,
        std::uint32_t height
        )
{
    // TODO: return platform specific window
    return std::make_unique<LinuxWindow>(title, width, height);
}

} // namespace SGE
