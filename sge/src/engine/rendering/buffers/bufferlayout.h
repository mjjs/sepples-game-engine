#ifndef _SGE_BUFFERLAYOUT_H
#define _SGE_BUFFERLAYOUT_H

#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <string>
#include <vector>

namespace SGE
{

enum class ShaderDataType {
    NONE = 0,
    VEC2,
    VEC3,
    VEC4,
    FLOAT,
};

struct BufferElement {
    std::string name;
    ShaderDataType type;
    std::uint32_t size;
    std::size_t offset = 0;
    bool normalized;

    BufferElement(ShaderDataType type, const std::string& name,
                  bool normalized = false);

    std::uint32_t component_count() const;
};

class BufferLayout
{
  private:
    std::uint32_t stride_ = 0;
    std::vector<BufferElement> elements_;

    void calculate_offsets_and_stride();

  public:
    BufferLayout() = default;
    BufferLayout(std::initializer_list<BufferElement> elements);
    std::uint32_t stride() const;
    const std::vector<BufferElement>& elements() const;

    std::vector<BufferElement>::iterator begin();
    std::vector<BufferElement>::iterator end();
    std::vector<BufferElement>::const_iterator begin() const;
    std::vector<BufferElement>::const_iterator end() const;
};

} // namespace SGE

#endif
