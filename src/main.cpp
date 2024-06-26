﻿#include <iostream>
#include <vector>
#include <string>

#include <yumi/yumi.hpp>

static float ambient = 0.0f;
static yumi::Shader* shader;

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    ambient += yoffset / 10.0f;

    if (ambient >= 1.0f)
        ambient = 1.0f;

    if (ambient <= 0.0f)
        ambient = 0.0f;

    shader->use();
    glUniform1f(shader->getUniformLocation("ambient"), ambient);
    shader->unuse();
}

int main(int argc, const char* argv[]) {
    yumi::EngineWindow window(1200, 600, "Yumi Deneme");

    shader = new yumi::Shader(
        yumi::ReadFile("shaders/default.vert"),
        yumi::ReadFile("shaders/default.frag")
    );

    yumi::Camera camera(&window, 45.0f, 0.1f, 1000.0f, 200.0f, 2.0f, 5.0f, glm::vec3(0.0f, 0.0f, -2.0f));
    yumi::Model model("res/models/crow/scene.gltf");

    shader->use();
    glUniform4fv(shader->getUniformLocation("lightColor"), 1, (float*)glm::value_ptr(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
    glUniform3fv(shader->getUniformLocation("lightPosition"), 1, (float*)glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
    glUniform1f(shader->getUniformLocation("ambient"), ambient);
    shader->unuse();

    glfwSetScrollCallback(window.get(), scrollCallback);

    while (!window.shouldClose()) {
        window.pollEvents();
        camera.processInputs();
        window.clear();

        if (window.input->getMouseButton(Yumi_MOUSE_BUTTON_LEFT)) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        if (window.input->getMouseButton(Yumi_MOUSE_BUTTON_MIDDLE)) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        }

        if (window.input->getMouseButton(Yumi_MOUSE_BUTTON_RIGHT)) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }

        if (window.input->getKey(Yumi_KEY_Q)) {
            model.transform.rotate(-1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        }

        if (window.input->getKey(Yumi_KEY_E)) {
            model.transform.rotate(1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        }

        model.render(shader, &camera);

        window.checkErrors();
        window.swapBuffers();
    }

    delete shader;
    shader->destroy();

    model.destroy();
    window.destroy();
    return 0;
}