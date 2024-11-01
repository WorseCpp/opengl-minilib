#include "VertexShader.hpp"

VertexShader::VertexShader(const char* source) {
    shaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shaderID, 1, &source, NULL);
    glCompileShader(shaderID);
    // Check for compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    glCheckError();
}

VertexShader::~VertexShader() {
    glDeleteShader(shaderID);
}

void VertexShader::bind(int shaderProgram) {
    glAttachShader(shaderProgram, shaderID);
}

