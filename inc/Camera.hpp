#include "glCommon.hpp"

//skuff AF
#ifndef CAMERA_H
enum Dirs
{
    FORWARD = 1,
    BACKWARD = -1
};


class Camera
{
    vec3 m_pos = vec3(0.f);
    vec3 m_dir = vec3(1.f, 0.f, 0.f);
    vec3 m_up = vec3(0.f, 1.f, 0.f);
    vec3 m_right = cross(m_dir, m_up);

    float phi = pi / 2.f;
    float theta = 0.f;
    const float cameraSpeed = 0.05f; // adjust accordingly
    const float cameraOmega = .005f;

public:

    Camera();
    Camera(const vec3& p, const vec3& d);

    mat4 getViewMatrix();

    void updateForward(Dirs dir);

    void updateRight(Dirs dir);

    void updateUp(Dirs dir);

    void rotateXY(double dx, double dy);

    vec3 getPos();
};
#endif

#define CAMERA_H