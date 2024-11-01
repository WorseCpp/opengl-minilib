#ifndef VERTEXSHADER_H
#include "glCommon.hpp"
#include <unordered_map>
class VertexShader {


public:
    // Constructor
    VertexShader(const char* source);

    // Destructor
    ~VertexShader();

    // Bind method
    void bind(int shaderProgram);

private:
    unsigned int shaderID;
};

#endif

#define  VERTEXSHADER_H