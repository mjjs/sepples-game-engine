#ifndef _SGE_UNIFORMBUFFER_H
#define _SGE_UNIFORMBUFFER_H

#include <cstdint>
#include <memory>

namespace SGE
{

class UniformBuffer
{
  public:
    UniformBuffer()          = default;
    virtual ~UniformBuffer() = default;

    UniformBuffer(const UniformBuffer&)  = delete;
    UniformBuffer(const UniformBuffer&&) = delete;
    UniformBuffer& operator=(const UniformBuffer&) = delete;
    UniformBuffer& operator=(const UniformBuffer&&) = delete;

    virtual void set_data(const void* data, std::uint32_t size,
                          std::uint32_t offset = 0) const = 0;

    static std::shared_ptr<UniformBuffer> create(std::uint32_t size,
                                                 std::uint32_t binding);
};

} // namespace SGE

#endif
