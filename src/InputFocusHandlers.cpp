#include "InputFocusHandlers.hpp"


FPSCameraInputHandler::FPSCameraInputHandler(shared_ptr<Camera>  c) 
: m_cam(c)
{
}

void FPSCameraInputHandler::handleKeyboard(GLFWwindow* window, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT) 
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);  
        m_mouseCaptured = false;
    }
    
    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS){
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
        m_mouseCaptured = true;
    }

    if (glfwGetKey(window, GLFW_KEY_DELETE) == GLFW_PRESS){
        //exit
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        m_cam->updateForward(FORWARD);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        m_cam->updateForward(BACKWARD);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        m_cam->updateRight(BACKWARD);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        m_cam->updateRight(FORWARD);

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        m_cam->updateUp(FORWARD);

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        m_cam->updateUp(BACKWARD);
}

void FPSCameraInputHandler::handleMouse(GLFWwindow* window, double xpos, double ypos, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT) {
    if (this->mouseCaptured()){
        //std::cout << xpos <<" " << ypos<< "\n";
        auto delx = xpos - SCR_WIDTH / 2;
        auto dely = (SCR_HEIGHT / 2) - ypos;

        glfwSetCursorPos(window, SCR_WIDTH / 2, SCR_HEIGHT / 2);

        m_cam->rotateXY(delx, dely);
    }
}

bool FPSCameraInputHandler::mouseCaptured() {return m_mouseCaptured;};
