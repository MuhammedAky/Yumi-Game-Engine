#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "shader.hpp"
#include "file.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include <iostream>

static yumi::Shader* shader;
int WIDTH   = 800;
int HEIGHT  = 600;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Square", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    glViewport(0, 0, WIDTH, HEIGHT);


    shader = new yumi::Shader(
        yumi::ReadFile("shaders/default.vert"),
        yumi::ReadFile("shaders/default.frag")
    );

    shader->use();

    // Vertex Data
    float vertices[] = {
        -0.5f, 0.5f, 0.0f,
         -0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
         0.5f, 0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         -0.5f,  -0.5f, 0.0f
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

    bool drawSquare = true;

    // Variables that help the rotation of the Square
    float rotation = 0.0f;
    double prevTime = glfwGetTime();

    float size = 1.0f;
    float color[4] = { 0.8f, 0.3f, 0.02f, 1.0f };
    float coords[3] = { 0.0f, 0.0f, 0.0f };

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Simple timer
        double crntTime = glfwGetTime();
        if (crntTime - prevTime >= 1 / 60)
        {
            rotation += 0.01f;
            prevTime = crntTime;
        }

        // Initializes matrices so they are not the null matrix
        glm::mat4 model     = glm::mat4(1.0f);
        glm::mat4 view      = glm::mat4(1.0f);
        glm::mat4 proj      = glm::mat4(1.0f);

        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
        proj = glm::perspective(glm::radians(45.0f), (float)WIDTH / HEIGHT, 0.1f, 100.0f);
        
        // Outputs the matrices into the Vertex Shader
        int modelLoc = glGetUniformLocation(shader->get_program_id(), "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        int viewLoc = glGetUniformLocation(shader->get_program_id(), "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        int projLoc = glGetUniformLocation(shader->get_program_id(), "proj");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

        if (drawSquare) {
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            shader->use();
        }

        ImGui::Begin("Test Windowww");
        ImGui::Text("Hello Wooorrlldd");
        ImGui::Checkbox("Draw Square", &drawSquare);
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
