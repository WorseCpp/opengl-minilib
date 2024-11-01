
#include "FragmentShader.hpp"
// Constructor implementation
FragmentShader::FragmentShader(const char* fragmentShaderSource) {
    int success;
    char infoLog[512];
    // fragment shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    glCheckError();
}

// Destructor implementation
FragmentShader::~FragmentShader() {
    // Cleanup code here
    glDeleteShader(fragmentShader);
}

// Method to bind the shader
void FragmentShader::bind(int shaderProgram) {
    // Code to bind the shader
    glAttachShader(shaderProgram, fragmentShader);
}



// ... existing code ...

