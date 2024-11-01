#include "Camera.hpp"

Camera::Camera(){}
Camera::Camera(const vec3& p, const vec3& d)
: m_pos(p), m_dir(d)
{}

mat4 Camera::getViewMatrix()
{
    return lookAt(m_pos, m_pos + m_dir, m_up);
}

void Camera::updateForward(Dirs dir)
{
    m_pos += m_dir * cameraSpeed * float(dir);
}

void Camera::updateRight(Dirs dir)
{
    m_pos += m_right * cameraSpeed * float(dir);
}

void Camera::updateUp(Dirs dir)
{
    m_pos += m_up * cameraSpeed * float(dir);
}

void Camera::rotateXY(double dx, double dy)
{
    //std::cout << dx << " " << dy << "\n";
    theta += cameraOmega * dx;
    phi -= cameraOmega * dy;
    phi = clamp(phi, 0.f, pi);
    m_dir = normalize(vec3(sin(phi) * cos(theta), cos(phi), sin(phi) * sin(theta)));
    m_right = -cross(m_up, m_dir);
}

vec3 Camera::getPos(){return m_pos;}