#include <yumi/vertexArray.hpp>

namespace yumi {
    VertexArray::VertexArray() {
        glGenVertexArrays(1, &id);
        glBindVertexArray(id);
    }

    VertexArray::~VertexArray() {

    }

    void VertexArray::linkAttrib(VertexBuffer* buffer, unsigned int index, GLenum type, unsigned int count, unsigned int stride, void* offset) {
        bind();
        buffer->bind();
        glVertexAttribPointer(index, count, type, GL_FALSE, stride, offset);
        glEnableVertexAttribArray(index);
        buffer->unbind();
        unbind();
    }

    void VertexArray::bind() {
        glBindVertexArray(id);
    }

    void VertexArray::unbind() {
        glBindVertexArray(0);
    }

    void VertexArray::destroy() {
        glDeleteVertexArrays(1, &id);
    }
}