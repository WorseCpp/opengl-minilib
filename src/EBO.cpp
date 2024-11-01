
#include "EBO.hpp"

// Function definitions

EBO::EBO()
{
    EBO(10000);    
}

EBO::EBO(int size)
{
    std::cout << "Allocating EBO of " << size << " indices.\n";
    glGenBuffers(1, &m_ID);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * size, NULL, GL_DYNAMIC_DRAW);
    glCheckError();

    m_max = size;

}


EBO::~EBO()
{
    glDeleteBuffers(1, &m_ID);
}


void EBO::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void EBO::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void EBO::addData(unsigned int* data, unsigned int num, int idx)
{
    assert(idx + num < m_max);
    bind();
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, idx * sizeof(unsigned int), sizeof(unsigned int) * num, data);
}
