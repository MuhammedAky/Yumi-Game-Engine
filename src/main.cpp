#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "shader.hpp"
#include "file.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

static yumi::Shader* shader;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Triangle", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    glViewport(0, 0, 800, 600);


    shader = new yumi::Shader(
        yumi::ReadFile("shaders/default.vert"),
        yumi::ReadFile("shaders/default.frag")
    );

    shader->use();

    // Vertex Data
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    bool drawTriangle = true;

    float size = 1.0f;
    float color[4] = { 0.8f, 0.3f, 0.02f, 1.0f };
    float coords[3] = { 0.0f, 0.0f, 0.0f };

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (drawTriangle) {
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            shader->use();
        }

        ImGui::Begin("Test Windowww");
        ImGui::Text("Hello Wooorrlldd");
        ImGui::Checkbox("Draw Triangle", &drawTriangle);
        ImGui::SliderFloat("Size", &size, 0.5f, 2.0f);
        ImGui::SliderFloat("X Coord", &coords[0], -0.5f, 0.5f);
        ImGui::SliderFloat("Y Coord", &coords[1], -0.5f, 0.5f);
        ImGui::SliderFloat("Z Coord", &coords[2], -0.5f, 0.5f);
        ImGui::ColorEdit4("Color", color);
        ImGui::End();

        // Get the locations of the size and color uniform variables
        int sizeLocation = shader->get_uniform_location("size");
        int coordsLocation = shader->get_uniform_location("coords");
        int colorLocation = shader->get_uniform_location("color");

        glUniform1f(sizeLocation, size);
        glUniform3f(coordsLocation, coords[0], coords[1], coords[2]);
        glUniform4f(colorLocation, color[0], color[1], color[2], color[3]);

        shader->use();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    shader->destroy();
    glfwTerminate();
    return 0;
}
