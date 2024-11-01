
#ifndef RENDERER_H
#include "glCommon.hpp"

#include "ShaderProgram.hpp"
#include "MemAlloc.hpp"
#include "Model.hpp"
#include "VAO.hpp"

namespace
{
    uint default_buffer_size = 1024; 
}

template<typename Vertex>
class Renderer
{
    public:

    unique_ptr<VAO<Vertex>> m_vao;
    unique_ptr<ShaderProgram> m_shader;
    
    unique_ptr<MemAlloc> m_vb_alloc;
    unique_ptr<MemAlloc> m_ib_alloc;
    
    vector<GraphicsModel<Vertex>> m_models;

    vector<mat4> m_modelMats;

    vector<void*> m_start_idxs;
    vector<uint> m_draw_lens;

    public:

    //In charge of rendering a buncha shit...

    Renderer(const string& fragSh, const string& vertSh, uint vb_siz=default_buffer_size, uint ib_siz=default_buffer_size)
    {
        m_shader = make_unique<ShaderProgram>(vertSh, fragSh);
        m_vao = make_unique<VAO<Vertex>>(vb_siz, ib_siz);
        m_vb_alloc = make_unique<SimpleMemAlloc>(vb_siz);
        m_ib_alloc = make_unique<SimpleMemAlloc>(ib_siz);
    }

    void addModel(Vertex* pvbuf, uint vNum, uint* pibuf, uint iNum, vec3 pos, vec3 orient)
    {
        //std::cout << "Renderer adding " << vNum << " " << iNum << "\n";
        vector<Vertex> vbuf;
        vector<uint> ibuf;

        for (int i = 0; i < vNum; i++)
        {
            vbuf.push_back(pvbuf[i]);
        }

        for (int i = 0; i < iNum; i++)
        {
            ibuf.push_back(pibuf[i]);
        }

        uint vbuf_idx = m_vb_alloc->alloc(vNum);
        uint ibuf_idx = m_ib_alloc->alloc(iNum);
        uint shader_num = m_models.size();

        m_models.push_back(GraphicsModel<Vertex>(vbuf, ibuf, vbuf_idx, ibuf_idx, shader_num, pos, orient));
    }

    void updateGeometryBuffers()
    {
        m_start_idxs = vector<void*>();
        m_draw_lens = vector<uint> ();
        
        m_vao->bind();
        int i = 0;
        for (auto& model : m_models)
        {
            m_draw_lens.push_back(0);
            m_start_idxs.push_back(0);
            if (model.hasNewGeometry())
            {
                auto geo_pair = model.getGeomForUpdate();
                auto vbuf = geo_pair.first;
                auto ibuf = geo_pair.second;

                m_vao->addData(&vbuf[0], vbuf.size(), &ibuf[0], ibuf.size(), model.getVbufIdx(), model.getIbufIdx());

                m_start_idxs[i] = (void*)(model.getIbufIdx() * sizeof(GLuint));
                m_draw_lens[i] = ibuf.size();
            }
            i++;
        }

        //m_draw_lens[0] = 100;
    }

    void setMVP(const mat4* mat)
    {
        m_shader->setUniform(mat, "MVP");
    }

    void updateModelMatricies()
    {
        m_modelMats = vector<mat4>();
        

        for (auto& model : m_models)
        {
            m_modelMats.push_back(model.getModelMatrix());
        }
        
        //std::cout << m_models.size() << "\n";
        m_shader->setUniformArr(&m_modelMats[0], m_models.size(), "ModelMatricies");
        //m_shader->setUniform(&mod, "Model");
    }

    void tickUpdate()
    {
        for (auto& model : m_models)
        {
            model.tickUpdate();
        }
    }

    void draw()
    {
        static_assert(sizeof(uint) == sizeof(GLint));
        static_assert(sizeof(uint) == sizeof(GLsizei));
        m_vao->bind();
        //m_shader->bind();
        glCheckError();

        //glDrawElements(GL_TRIANGLES, 9*3, GL_UNSIGNED_INT, 0);

        //std::cout << m_draw_lens.size() << "\n";
        //for (int i = 0; i < m_draw_lens.size() ; i++)
        //{
        //    std::cout << " Drawing " << m_draw_lens[i] <<" at " << m_start_idxs[i] << "\n";
        //}

        auto addr_ptr = &m_start_idxs[0];


        //const void* indices[3] = {
        //    (void*)(0  * sizeof(GLuint)),   // Offset for first draw command
        //    (void*)(9  * sizeof(GLuint)),   // Offset for second draw command
        //    (void*)(18 * sizeof(GLuint))    // Offset for third draw command
        //};

        glMultiDrawElements(GL_TRIANGLES,  (GLsizei*) &m_draw_lens[0], GL_UNSIGNED_INT, (const void * const*) addr_ptr, m_draw_lens.size());
        glCheckError();
    }

    void bind()
    {
        m_shader->bind();
        m_vao->bind();
    }

};

#endif


#define RENDERER_H