#ifndef VAO_h

#include "glCommon.hpp"

#include "Vertices.hpp"
#include "VBO.hpp"
#include "EBO.hpp"



template<typename Vertex>
class VAO
{
    public:
    
    unsigned int m_ID;
    
    unique_ptr<VBO<Vertex>> m_VBO = nullptr;
    unique_ptr<EBO> m_EBO         = nullptr;

    VAO(uint vbo_siz = 100, uint ibo_siz = 100)
    {
        glCheckError();
        glGenVertexArrays(1, &m_ID);
        glCheckError();
        m_VBO = make_unique<VBO<Vertex>>(vbo_siz);
        glCheckError();

        m_EBO = make_unique<EBO>(ibo_siz);

        glCheckError();

        bind();

        // set opengl attrib ptrs
        const Vertex * def = (Vertex*)this;
        set_attrib(def);
        glCheckError();
    }
    ~VAO(){

        bind();
        m_VBO = nullptr;
        m_EBO = nullptr; //destroy ebo and vbo
        

        glDeleteVertexArrays(1, &m_ID);
    }; // Destructor declaration

    void bind_vao()
    {
        glBindVertexArray(m_ID);
    }
    void unbind_vao()
    {
        glBindVertexArray(0);
    }

    void bind()
    {
        bind_vao();
        m_VBO->bind();
        m_EBO->bind();
    } // bind function declaration

    void unbind()
    {
        glBindVertexArray(0);
        m_VBO->unbind();
        m_EBO->unbind();
    }

    void addData(Vertex* vert, int numV, unsigned int* ind, int numI)
    {
        std::cout << "Adding " << numV <<" Verts and " << numI <<" Inds...\n";
        m_VBO->addData(vert, numV, 0);
        m_EBO->addData(ind, numI, 0);
    }

    void addData(Vertex* vert, int numV, unsigned int* ind, int numI, int vidx, int iidx)
    {
        std::cout << "Adding to VAO = " <<  m_ID << "\n";
        std::cout << "  Adding " << numV <<" Verts and " << numI <<" Inds...\n";
        std::cout << "  Adding at index " << vidx <<" (v) and " << iidx << " (i) \n";
        m_VBO->addData(vert, numV, vidx);
        m_EBO->addData(ind, numI, iidx);
    }

    //debug only :D :D
    void draw()
    {
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
    }

    VBO<Vertex>& getVBO()
    {
        return *m_VBO;
    }

    EBO& getEBO()
    {
        return *m_EBO;
    }
};

#endif

#define VAO_h