#ifndef _SGE_VERTEXBUFFER_H
#define _SGE_VERTEXBUFFER_H

#include "vertex.h"

#include <cstdint>
#include <vector>

namespace SGE {

class VertexBuffer {
    public:
        VertexBuffer() = default;
        virtual ~VertexBuffer() = default;
        virtual void bind() const = 0;

        VertexBuffer(const VertexBuffer&) = delete;
        VertexBuffer(const VertexBuffer&&) = delete;
        VertexBuffer& operator=(const VertexBuffer&) = delete;
        VertexBuffer& operator=(const VertexBuffer&&) = delete;

        static VertexBuffer* create(const std::vector<Vertex>& vertices);
};

} // SGE

#endif
