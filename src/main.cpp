#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include "ShaderProgram.hpp"
#include <fstream>
#include "VAO.hpp"
#include "Camera.hpp"
#include "InputFocusHandlers.hpp"
#include "Renderer.hpp"

// settings
unsigned int SCR_WIDTH = 1600;
unsigned int SCR_HEIGHT = 800;

shared_ptr<InputFocusHandler> inputHandler;

shared_ptr<Camera> cam;
GLFWwindow* window;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    inputHandler->handleMouse(window, xpos, ypos, SCR_WIDTH, SCR_HEIGHT);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    inputHandler->handleKeyboard(window, SCR_WIDTH, SCR_HEIGHT);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
}

int main()
{
    //initialize input handlers
    cam = make_shared<Camera>(vec3(-10., 0., 0.), vec3(1., 0., 0.));

    inputHandler = make_shared<FPSCameraInputHandler>(cam);

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetCursorPosCallback(window, mouse_callback);  
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    glClearDepth(1.0f);                   // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    
    glCheckError();    

    //This context is for OpenGL objects because their destructors need to run BEFORE glfw destructors
    {


        Renderer renderer = Renderer<ModelV3>("simple_fshader.glsl", "simple_vshader.glsl");

        // build and compile our shader program
        // ------------------------------------
        // vertex shader
        //ShaderProgram& shad = *renderer.m_shader; //("simple_vshader.glsl", "simple_fshader.glsl");
        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        
        ModelV3 vertices[] = {
            {0.5f,  0.5f, 0.0f , 0.0f, 0, 0. },  // top right
            {0.5f, -0.5f, 0.0f , 0.0f, 0, 1. },  // bottom right
            {-0.5f, -0.5f, 0.0f, 0.0f, 0, 5. },  // bottom left
            {-0.5f,  0.5f, 0.0f, 0.0f, 0, 0. },   // top left 
            {1.f,  1.f,    1.0f, 0.0f, 0, 1. },  // top right
            {0.5f, -0.5f,  0.0f, 0.0f, 0, .5 }  // bottom right
        };
        /*
        ModelV3 vertices[] = {
            {0.5f,  0.5f, 0.0f , 0.0f},  // top right
            {0.5f, -0.5f, 0.0f , 0.0f},  // bottom right
            {-0.5f, -0.5f, 0.0f, 0.0f},  // bottom left
            {-0.5f,  0.5f, 0.0f, 0.0f},   // top lef
            {1.f,  1.f, 1.0f,    0.0f},  // top right
            {0.5f, -0.5f, 0.0f,  0.0f}  // bottom right
        };*/


        unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,  // first Triangle
            1, 2, 3,   // second Triangle
            3, 4, 5
        };

        renderer.addModel((ModelV3*) vertices, 6, indices, 9, vec3(0.0, 0., 0.), vec3(0.));

        renderer.addModel((ModelV3*) vertices, 6, indices, 9, vec3(0.0, 0.0, -10.0), vec3(0.));

        renderer.addModel((ModelV3*) vertices, 6, indices, 9, vec3(0.0, 0.0, 10.0), vec3(0.));


        renderer.updateGeometryBuffers();



        // uncomment this call to draw in wireframe polygons.
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        // render loop
        // -----------

        while (!glfwWindowShouldClose(window))
        {
            // input
            // -----
            processInput(window);

            // render
            // ------
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // draw our first triangle
            //shad.bind();

            mat4 projection = perspective(90.f, 1.0f, .1f, 100.0f);

            mat4 MVP = projection * cam->getViewMatrix();

            renderer.bind();// seeing as we only have a single VAO_id there's no need to bind it every time, but we'll do so to keep things a bit more organized

            renderer.setMVP(&MVP);

            //std::cout << "drawing....??\n\n";
            renderer.tickUpdate();
            renderer.updateModelMatricies();
            renderer.draw();
            //vao.draw();
            // glBindVertexArray(0); // no need to unbind it every time 
    
            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            // -------------------------------------------------------------------------------
            glfwSwapBuffers(window);
            glfwPollEvents();

        }

    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}





