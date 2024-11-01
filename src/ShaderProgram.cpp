#include "ShaderProgram.hpp"
#include <fstream>
// ... existing code ...

ShaderProgram::ShaderProgram(const std::string& vertexShaderFile, const std::string& fragmentShaderFile) {
    
    m_ID = glCreateProgram(); //ShaderProgram("simple_vshader.glsl", "simple_fshader.glsl");
    glCheckError();
    //bind();
    {
        //std::string vertexShaderFile = "simple_vshader.glsl";
        //std::string fragmentShaderFile = "simple_fshader.glsl";
        // Constructor implementation
        std::ifstream vertexFile(vertexShaderFile);
        std::ifstream fragmentFile(fragmentShaderFile);

        std::string vertexCode;
        std::string fragmentCode;
        

        if (vertexFile.is_open()) {
            vertexCode = std::string((std::istreambuf_iterator<char>(vertexFile)), std::istreambuf_iterator<char>());

            vertexFile.close();
        }
        else
        {
            std::cout << "File '" << vertexShaderFile << "' can't be opened...\n";
            assert(false);
        }

        if (fragmentFile.is_open()) {
            fragmentCode = std::string((std::istreambuf_iterator<char>(fragmentFile)), std::istreambuf_iterator<char>());
            // Process fragmentCode as needed


            fragmentFile.close();
        }
        else
        {
            std::cout << "File '" << fragmentShaderFile << "' can't be opened...\n";
            assert(false);
        }

        glCheckError();
        m_v = make_shared<VertexShader>(vertexCode.c_str());
        // check for shader compile errors
        int success;
        char infoLog[512];

        // fragment shader
        m_f = make_shared<FragmentShader>(fragmentCode.c_str());
        // link shaders

        m_v->bind(m_ID);
        m_f->bind(m_ID);
        glCheckError();
        glLinkProgram(m_ID);
        // check for linking errors
        glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        glCheckError();
    }    
}

ShaderProgram::~ShaderProgram() {
    // Destructor implementation
    glDeleteProgram(m_ID);
}

void ShaderProgram::bind() {
    // Bind implementation
    glUseProgram(m_ID);
}


int ShaderProgram::lookup_uniform_loc(const std::string& name)
{
    if (m_uniform_loc.find(name) != m_uniform_loc.end())
    {
        return m_uniform_loc[name];
    }

    glCheckError();
    
    auto loc = glGetUniformLocation(m_ID, name.c_str());
    
    m_uniform_loc[name] = loc;
    
    glCheckError();
    
    return loc;
}

void ShaderProgram::setUniform(const mat4* m, const std::string& name)
{
    bind();
    glCheckError();
    unsigned int transformLoc = lookup_uniform_loc(name);
    glCheckError();
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, (GLfloat*) m);
    glCheckError();
}

void ShaderProgram::setUniformArr(const mat4* m, uint num, const std::string& name)
{
    glCheckError();
    bind();
    glCheckError();
    auto loc = lookup_uniform_loc(name);
    glCheckError();

    glUniformMatrix4fv(loc, num, GL_FALSE, (GLfloat*) m);
    glCheckError();
}