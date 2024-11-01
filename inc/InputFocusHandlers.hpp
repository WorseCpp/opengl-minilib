#include "glCommon.hpp"
#include "Camera.hpp"

//A class for processing keyboard and mouse inputs
class InputFocusHandler
{
    public:
    virtual void handleKeyboard(GLFWwindow* window, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT){}
    virtual void handleMouse(GLFWwindow* window, double xpos, double ypos, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT){}
    virtual bool mouseCaptured() {return false;};
};


class FPSCameraInputHandler : public InputFocusHandler
{
private:
    shared_ptr<Camera> m_cam;
    bool m_mouseCaptured = true;
public:
    FPSCameraInputHandler(shared_ptr<Camera>  c);
    void handleKeyboard(GLFWwindow* window, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT) override;
    void handleMouse(GLFWwindow* window, double xpos, double ypos, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT) override;
    bool mouseCaptured() override;
};