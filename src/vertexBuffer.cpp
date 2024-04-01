#include <yumi/vertexBuffer.hpp>

namespace yumi {
    VertexBuffer::VertexBuffer(std::vector <Vertex>& vertices) {
        glGenBuffers(1, &id);
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    VertexBuffer::~VertexBuffer() {

    }

    void VertexBuffer::bind() {
        glBindBuffer(GL_ARRAY_BUFFER, id);
    }

    void VertexBuffer::unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::destroy() {
        glDeleteBuffers(1, &id);
    }
}