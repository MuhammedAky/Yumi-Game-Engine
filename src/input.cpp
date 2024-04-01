#include <yumi/input.hpp>

namespace yumi {
    Input::Input(GLFWwindow* window) : window(window) {

    }

    Input::~Input() {

    }

    bool Input::getKey(int key) {
        return glfwGetKey(window, key);
    }

    bool Input::getMouseButton(int button) {
        return glfwGetMouseButton(window, button);
    }

    void Input::getMousePosition(double* x, double* y) {
        glfwGetCursorPos(window, x, y);
    }

    void Input::setMousePosition(double x, double y) {
        glfwSetCursorPos(window, x, y);
    }

    void Input::setMouseVisible(bool visible) {
        glfwSetInputMode(window, GLFW_CURSOR, !visible ? GLFW_CURSOR_HIDDEN : GLFW_CURSOR_NORMAL);
    }
}