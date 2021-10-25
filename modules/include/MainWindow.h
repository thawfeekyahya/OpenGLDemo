#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

class MainWindow {

private:
    GLFWwindow* window;
    int screenWidth  = 800;
    int screenHeight = 800;
    bool fullScreen   = false;
    bool wireFrameMode = false;
    const char* screenTitle = "Introduction to Modern OpenGL - Hello Shaders";
    static void handleKeyPress(GLFWwindow* window,int key,int scancode,int action,int mode);
    


public:
    MainWindow();
    void setScreenSize(int pWidth,int pHeight);
    GLFWwindow* initOpenGL();
    void showFPS();
};




