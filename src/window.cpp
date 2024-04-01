#include <yumi/window.hpp>

namespace yumi {
    EngineWindow::EngineWindow(int32_t width, int32_t height, const char* title, const char* iconPath, Color backgroundColor, bool fullscreen, bool resizable, bool vsync)
        : backgroundColor(backgroundColor), title(title), iconPath(iconPath), width(width), height(height), resizable(resizable), vsync(vsync), lastTime(0.0), currentTime(0.0), deltaTime(0.0) {

        glfwInit();
        glfwWindowHint(GLFW_RESIZABLE, resizable ? GLFW_TRUE : GLFW_FALSE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);

        if (width == -1)
            this->width = videoMode->width;

        if (height == -1)
            this->height = videoMode->height;

        window = glfwCreateWindow(width, height, title, fullscreen ? primaryMonitor : nullptr, nullptr);
        glfwMakeContextCurrent(window);

        if (iconPath != nullptr) {
            GLFWimage images[1];
            stbi_set_flip_vertically_on_load(false);
            images[0].pixels = stbi_load(iconPath, &images[0].width, &images[0].height, 0, 4);
            glfwSetWindowIcon(window, 1, images);
            stbi_image_free(images[0].pixels);
        }

        glfwSwapInterval(vsync ? 1 : 0);
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        glViewport(0, 0, width, height);
        glClearColor(backgroundColor.getRf(), backgroundColor.getGf(), backgroundColor.getBf(), backgroundColor.getAf());

        input = new Input(window);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        glFrontFace(GL_CCW);
    }

    EngineWindow::~EngineWindow() {

    }

    bool EngineWindow::shouldClose() {
        return glfwWindowShouldClose(window);
    }

    int32_t EngineWindow::checkErrors(bool log) {
        int32_t error = glGetError();
        if (error && log) std::cout << "VEGA: ERROR: " << error << std::endl;
        return error;
    }

    void EngineWindow::destroy() {
        delete input;

        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void EngineWindow::clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }

    void EngineWindow::swapBuffers() {
        glfwSwapBuffers(window);
    }

    void EngineWindow::pollEvents() {
        glfwMakeContextCurrent(window);
        glfwPollEvents();

        int32_t width, height;
        glfwGetWindowSize(window, &width, &height);

        if (width != this->width || height != this->height) {
            this->width = width, this->height = height;
            glViewport(0, 0, width, height);
        }

        currentTime = glfwGetTime();

        if (lastTime == 0.0f)
            lastTime = currentTime;

        deltaTime = currentTime - lastTime;
        lastTime = currentTime;
    }

    void EngineWindow::setIcon(const char* iconPath) {
        if (iconPath != nullptr) {
            GLFWimage images[1];
            stbi_set_flip_vertically_on_load(false);
            images[0].pixels = stbi_load(iconPath, &images[0].width, &images[0].height, 0, 4);
            glfwSetWindowIcon(window, 1, images);
            stbi_image_free(images[0].pixels);
        } this->iconPath = iconPath;
    }

    const std::string& EngineWindow::getIconPath() {
        return iconPath;
    }

    const std::string& EngineWindow::getTitle() {
        return title;
    }

    void EngineWindow::setTitle(const char* title) {
        this->title = title;
    }

    void EngineWindow::getSize(int32_t* width, int32_t* height) {
        glfwGetWindowSize(window, width, height);
    }

    void EngineWindow::setSize(int32_t width, int32_t height) {
        glfwSetWindowSize(window, width, height);
        glViewport(0, 0, width, height);
    }

    Color* EngineWindow::getBackgroundColor() {
        return &backgroundColor;
    }

    void EngineWindow::setBackgroundColor(Color backgroundColor) {
        this->backgroundColor = backgroundColor;
    }

    void EngineWindow::setVsync(bool vsync) {
        glfwSwapInterval(vsync ? 1 : 0);
        this->vsync = vsync;
    }

    bool EngineWindow::getVsync() {
        return vsync;
    }

    GLFWwindow* EngineWindow::get() {
        return window;
    }
}