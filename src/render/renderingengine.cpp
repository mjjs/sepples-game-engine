#include "gameobject.h"
#include "renderingengine.h"
#include "basicshader.h"

#include <cstddef>
#include <string>

SGE::RenderingEngine::RenderingEngine(
        const std::size_t width,
        const std::size_t height,
        const std::string& window_title) :
    window_{width, height, window_title}
{
}

void SGE::RenderingEngine::render(const GameObject& gameobject) const
{
    window_.clear();

    BasicShader shader{};
    gameobject.render(shader);

    window_.flip();
}
