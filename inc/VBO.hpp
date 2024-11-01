
#ifndef VBO_h

#include "glCommon.hpp"


template<typename Vertex>
class VBO
{
    unsigned int m_ID;
    uint m_max;
public:
    VBO();
    VBO(int size); // Constructor declaration
    ~VBO(); // Destructor declaration
    void bind(); // bind function declaration
    void addData(Vertex* data, unsigned int num, int idx); // addData function declaration
    void unbind();
};

// Function definitions


template<typename Vertex>
VBO<Vertex>::VBO()
{
    VBO(10000);
}

template<typename Vertex>
VBO<Vertex>::VBO(int size)
{
    std::cout << "Allocating VBO of " << size << " vertices (" << size * sizeof(Vertex) << " bytes).\n";
    glGenBuffers(1, &m_ID);
    bind();
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * size, NULL, GL_DYNAMIC_DRAW);
    glCheckError();

    m_max = size;
}

template<typename Vertex>
VBO<Vertex>::~VBO()
{
    glDeleteBuffers(1, &m_ID);
}

template<typename Vertex>
void VBO<Vertex>::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

template<typename Vertex>
void VBO<Vertex>::addData(Vertex* data, unsigned int num, int idx)
{
    assert(idx + num < m_max);
    bind();
    glBufferSubData(GL_ARRAY_BUFFER, idx * sizeof(Vertex), sizeof(Vertex) * num, data);
}

template<typename Vertex>
void VBO<Vertex>::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

#endif

#define VBO_h