#include "Vertices.hpp"

void set_attrib(const v3 * in)
{
    std::cout << "Setting attribute ptr for class 'v3'\n";

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void set_attrib(const ModelV3 * in)
{
    std::cout << "Setting attribute ptr for class 'ModelV3'\n";

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(ModelV3), (void*)offsetof(ModelV3, xyzw));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(ModelV3), (void*)offsetof(ModelV3, model));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(ModelV3), (void*)offsetof(ModelV3, col));
    glEnableVertexAttribArray(2);
    
}