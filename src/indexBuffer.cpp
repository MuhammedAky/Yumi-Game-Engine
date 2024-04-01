#include <yumi/indexBuffer.hpp>


namespace yumi {
    IndexBuffer::IndexBuffer(std::vector <unsigned int>& indices) : count(indices.size()) {
        glGenBuffers(1, &id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    IndexBuffer::~IndexBuffer() {

    }

    int IndexBuffer::getCount() {
        return count;
    }

    void IndexBuffer::bind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    }

    void IndexBuffer::unbind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void IndexBuffer::destroy() {
        glDeleteBuffers(1, &id);
    }
}