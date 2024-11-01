
#ifndef MODEL_H
#include "glCommon.hpp"


//this is a convenience class
//Not a strandalone
//exists only to store data conveniently for a renderer class
template<typename Vertex>
class GraphicsModel 
{
    private:
        vector<Vertex> m_vbuf;
        vector<uint> m_ibuf;
        vec3 m_location = vec3(0.);
        //euler angles in radians
        vec3 m_orientation = vec3(0.f, 0.f, 0.f);

        bool m_transmatrix_updated = false;
        bool m_orientatmatrix_updated = false;
        

        mat4 m_translation_mat;
        mat4 m_orientation_mat;

        //Is the geometry on the vbuffer updater??
        bool geometryUpdated = true;

        uint m_vbuf_idx;
        uint m_ibuf_idx;
        uint m_uniform_loc;

        uint m_max_verts;
        uint m_max_idx;

    public:

        GraphicsModel(vector<Vertex> vbuf_in, vector<uint> ibuf_in, uint vindx, uint iindx, uint uloc, vec3 pos, vec3 orie)
        : m_vbuf(vbuf_in), m_ibuf(ibuf_in), m_vbuf_idx(vindx), m_ibuf_idx(iindx), m_uniform_loc(uloc), m_location(pos), m_orientation(orie)
        {
            geometryUpdated = false;
            m_max_verts = vbuf_in.size();
            m_max_idx = ibuf_in.size();

            for (auto& vert : m_vbuf)
            {
                vert.model = uloc;
                //vert.xyzw[0] += pos.x;
                //vert.xyzw[1] += pos.y;
                //vert.xyzw[2] += pos.z;
            }

            for (auto& idx : m_ibuf)
            {
                idx += vindx; 
            }

            for (int i = 0; i < m_vbuf.size(); i++)
            {
                std::cout << m_vbuf[i].xyzw[3] << " ";
                std::cout << m_vbuf[i].xyzw[0] << " "<< m_vbuf[i].xyzw[1] << " "<< m_vbuf[i].xyzw[2] << "\n";
            }


            std::cout << "Making Graphics Model, uniform at " << uloc << "\n";
        }

        bool hasNewGeometry()
        {
            return ! geometryUpdated;
        }

        pair<vector<Vertex>, vector<uint>> getGeomForUpdate()
        {
            geometryUpdated = true;
            return pair<vector<Vertex>, vector<uint>>(m_vbuf, m_ibuf);
        }

        uint getVbufIdx()
        {
            return m_vbuf_idx;
        }

        uint getIbufIdx()
        {
            return m_ibuf_idx;
        }

        uint getUniformIdx()
        {
            return m_uniform_loc;
        }

        const mat4& getTransMatrix()
        {
            //std::cout << "Trans Mtarix being made...\n";
            if (m_transmatrix_updated)
            {
                return m_translation_mat;
            } 
            m_transmatrix_updated = true;
            return m_translation_mat = translate(mat4(1.0f), m_location);
        }

        const mat4& getOrientMatrix()
        {
            //std::cout << "Orienta Mtarix being made...\n";
            if (m_orientatmatrix_updated)
            {
                return m_orientation_mat;
            } 
            m_orientatmatrix_updated = true;

            mat4 ormat = mat4(1.0f);

            ormat = rotate(ormat, m_orientation.x, vec3(1.0, 0.0, 0.0));
            ormat = rotate(ormat, m_orientation.y, vec3(0.0, 1.0, 0.0));
            ormat = rotate(ormat, m_orientation.z, vec3(0.0, 0.0, 1.0));

            return m_orientation_mat = ormat;
        }

        mat4 getModelMatrix()
        {
            //std::cout << "Model Mtarix being made...\n";
            auto tmat = getTransMatrix();
            //std::cout << "tmat done\n";
            auto omat = getOrientMatrix();
            //std::cout << "omat done\n\n";

            //std::cout << "Matrix to translate to " << m_location.x <<" " << m_location.y << " " << m_location.z << "\n";
            //std::cout << to_string(tmat) << "\n" << to_string(omat) << "\n";

            return tmat * omat;
        }

        void tickUpdate()
        {
            m_orientatmatrix_updated = false;
            m_transmatrix_updated = false;

            //m_location.y += .01 * m_uniform_loc;

            m_orientation.x += 0.01 * m_uniform_loc;
        }
};

#endif


#define MODEL_H