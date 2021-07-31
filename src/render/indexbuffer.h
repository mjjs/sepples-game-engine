#ifndef _SGE_INDEXBUFFER_H
#define _SGE_INDEXBUFFER_H

#include "vertex.h"

#include <cstddef>
#include <cstdint>
#include <vector>

namespace SGE {

class IndexBuffer {
    public:
        IndexBuffer() = default;
        virtual ~IndexBuffer() = default;
        virtual void bind() const = 0;

        IndexBuffer(const IndexBuffer&) = delete;
        IndexBuffer(const IndexBuffer&&) = delete;
        IndexBuffer& operator=(const IndexBuffer&) = delete;
        IndexBuffer& operator=(const IndexBuffer&&) = delete;

        virtual std::size_t count() const = 0;

        static IndexBuffer* create(const std::vector<int>& indices);
};

} // SGE

#endif
