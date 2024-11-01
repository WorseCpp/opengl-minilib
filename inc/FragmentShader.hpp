// glfw_tst/FragmentShader.hpp

#ifndef FRAG_SH_H
#include "glCommon.hpp"

class FragmentShader {
private:
    int fragmentShader;
public:
    FragmentShader(const char* fragmentShaderSource); // Constructor
    ~FragmentShader(); // Destructor

    void bind(int shaderProgram); // Method to bind the shader

    // ... existing code ...
};
#endif
#define FRAG_SH_H