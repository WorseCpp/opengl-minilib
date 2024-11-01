#ifndef SHAD_PROG_H

#include "VertexShader.hpp"
#include "FragmentShader.hpp"


class ShaderProgram {

    unsigned int m_ID;
    shared_ptr<VertexShader> m_v;
    shared_ptr<FragmentShader> m_f;

    std::unordered_map<std::string, unsigned int> m_uniform_loc;

    int lookup_uniform_loc(const std::string& name);

public:
    ShaderProgram(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
    ~ShaderProgram();
    void bind();
    // ... existing code ...
    shared_ptr<VertexShader> getVShad();
    shared_ptr<FragmentShader> getFShad();
        
    void setUniform(const mat4* m, const std::string& name); 

    void setUniformArr(const mat4* m, uint num, const std::string& name); 

};

#endif 

#define SHAD_PROG_H