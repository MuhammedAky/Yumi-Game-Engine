#include <yumi/shader.hpp>

namespace yumi {
    Shader::Shader(std::string vertexSourceString, std::string fragmentSourceString) {
        id = glCreateProgram();

        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        const char* vertexSource = vertexSourceString.c_str();
        const char* fragmentSource = fragmentSourceString.c_str();

        glShaderSource(vertexShader, 1, &vertexSource, nullptr);
        glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);

        glCompileShader(vertexShader);
        checkShader(vertexShader, "vertex");
        glCompileShader(fragmentShader);
        checkShader(fragmentShader, "fragment");

        glAttachShader(id, vertexShader);
        glAttachShader(id, fragmentShader);
        glLinkProgram(id);
        checkProgram();

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    Shader::~Shader() {

    }

    void Shader::checkProgram() {
        int status;
        glGetProgramiv(id, GL_LINK_STATUS, &status);

        if (status == GL_FALSE) {
            char log[1024];
            glGetProgramInfoLog(id, 1024, nullptr, log);
            std::cout << log << std::endl;
        }
    }

    void Shader::checkShader(unsigned int shader, const char* type) {
        int status;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

        if (status == GL_FALSE) {
            char log[1024];
            glGetShaderInfoLog(shader, 1024, nullptr, log);
            std::cout << log << std::endl;
        }
    }

    int Shader::getUniformLocation(const char* name) {
        return glGetUniformLocation(id, name);
    }

    void Shader::use() {
        glUseProgram(id);
    }

    void Shader::unuse() {
        glUseProgram(0);
    }

    void Shader::destroy() {
        glDeleteProgram(id);
    }
}