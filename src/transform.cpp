#include <yumi/transform.hpp>

namespace yumi {
    Transform::Transform() {
        reset();
    }

    Transform::~Transform() {

    }

    void Transform::translate(glm::vec3 value) {
        transform = glm::translate(transform, value);
    }

    void Transform::rotate(float angle, glm::vec3 axis) {
        transform = glm::rotate(transform, glm::radians(angle), axis);
    }

    void Transform::scale(glm::vec3 value) {
        transform = glm::scale(transform, value);
    }

    void Transform::reset() {
        transform = glm::mat4(1.0f);
    }

    void Transform::uniform(unsigned int id) {
        glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(transform));
    }

    glm::mat4* Transform::get() {
        return &transform;
    }
    void Transform::set(glm::mat4* matrix) {
        transform = *matrix;
    }

    void Transform::destroy() {

    }
}