#include "engine/rendering/buffers/bufferlayout.h"

#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <string>
#include <vector>

namespace SGE {

    static std::uint32_t shader_data_type_size(ShaderDataType type)
    {
        switch(type) {
        case ShaderDataType::NONE: return -1;
        case ShaderDataType::VEC2: return sizeof(float) * 2;
        case ShaderDataType::VEC3: return sizeof(float) * 3;
        }
    }

    BufferElement::BufferElement(ShaderDataType type, const std::string& name,
            bool normalized)
        : name{name},
          type{type},
          size{shader_data_type_size(type)},
          normalized{normalized}
    {
    }

    std::uint32_t BufferElement::component_count() const
    {
        switch (type) {
        case ShaderDataType::NONE: return 0;
        case ShaderDataType::VEC2: return 2;
        case ShaderDataType::VEC3: return 3;
        }
    }

    BufferLayout::BufferLayout(std::initializer_list<BufferElement> elements)
        : elements_{elements}
    {
        calculate_offsets_and_stride();
    }

    std::uint32_t BufferLayout::stride() const
    {
        return stride_;
    }

    void BufferLayout::calculate_offsets_and_stride()
    {
        std::size_t offset = 0;
        stride_ = 0;

        for (auto& element : elements_) {
            element.offset = offset;
            offset += element.size;
            stride_ += element.size;
        }
    }

    const std::vector<BufferElement>& BufferLayout::elements() const
    {
        return elements_;
    }

    std::vector<BufferElement>::iterator BufferLayout::begin()
    {
        return elements_.begin();
    }

    std::vector<BufferElement>::iterator BufferLayout::end()
    {
        return elements_.end();
    }

    std::vector<BufferElement>::const_iterator BufferLayout::begin() const
    {
        return elements_.begin();
    }

    std::vector<BufferElement>::const_iterator BufferLayout::end() const
    {
        return elements_.end();
    }

} // namespace SGE
