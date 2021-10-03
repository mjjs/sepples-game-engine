#include "platform/opengl/openglframebuffer.h"

#include <cassert>
#include <glad/glad.h>

namespace SGE
{

OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferConfig& config)
    : config_{config}
{
    initialize();
}

OpenGLFramebuffer::~OpenGLFramebuffer()
{
    glDeleteFramebuffers(1, &buffer_id_);
    glDeleteTextures(1, &depth_attachment_id_);
    glDeleteTextures(1, &colour_attachment_id_);
}

void OpenGLFramebuffer::initialize()
{
    if (buffer_id_ != 0) {
        glDeleteFramebuffers(1, &buffer_id_);
        glDeleteTextures(1, &depth_attachment_id_);
        glDeleteTextures(1, &colour_attachment_id_);
    }

    glCreateFramebuffers(1, &buffer_id_);
    glBindFramebuffer(GL_FRAMEBUFFER, buffer_id_);

    glCreateTextures(GL_TEXTURE_2D, 1, &colour_attachment_id_);
    glBindTexture(GL_TEXTURE_2D, colour_attachment_id_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, config_.width, config_.height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                           colour_attachment_id_, 0);

    glCreateTextures(GL_TEXTURE_2D, 1, &depth_attachment_id_);
    glBindTexture(GL_TEXTURE_2D, depth_attachment_id_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, config_.width,
                 config_.height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8,
                 nullptr);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                           GL_TEXTURE_2D, depth_attachment_id_, 0);

    assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGLFramebuffer::bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, buffer_id_);
    glViewport(0, 0, config_.width, config_.height);
}

void OpenGLFramebuffer::unbind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGLFramebuffer::resize(const std::uint32_t width,
                               const std::uint32_t height)
{
    if (width == 0 || height == 0) {
        return;
    }

    config_.height = height;
    config_.width  = width;

    initialize();
}

} // namespace SGE
