
#include "mainwindow.h"

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <string>
#include <iostream>
#include <functional> 

using namespace std;

MainWindow::MainWindow() {
}

unsigned MainWindow::getWidth() const {
    return m_width;
}

unsigned MainWindow::getHeight() const {
    return m_height;
}

void MainWindow::loop(std::function<void()> func,GLFWwindow* window) {



    while(!glfwWindowShouldClose(window)) {

       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       
       func();

       glfwPollEvents();
       glfwSwapBuffers(window);
       
       if (GLFW_PRESS == glfwGetKey(window,GLFW_KEY_ESCAPE)) {
           glfwSetWindowShouldClose(window,1);
       }
    }    
}


void MainWindow::glfw_frameBuffer_callback(GLFWwindow* window,unsigned width,unsigned height) {
   buffer_window_height = height;
   buffer_window_width = width;
}

void MainWindow::glfw_windowSize_callback(GLFWwindow* window,unsigned width,unsigned height) {
    global_window_height = height;
    global_window_width = width;
}

int MainWindow::initialize() {
    if (!glfwInit()) {
        cerr<<"Could not launch GLFW Window"<<endl;
        return 1;
    }
    return 0;
}


GLFWwindow* MainWindow::createWindow(unsigned width,unsigned height,std::string title) {

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(width,height,title.c_str(),NULL,NULL);
    m_width = width;
    m_height = height;
    m_title = title;
    
    //Check primary monitor
    
    GLFWmonitor* mon = glfwGetPrimaryMonitor();
    const GLFWvidmode* vmode = glfwGetVideoMode(mon);
    
    //m_window = glfwCreateWindow(vmode->width,vmode->height,title.c_str(),mon,NULL);
    
    return m_window;
}

void MainWindow::makeEnv(GLFWwindow* window) {

   glfwMakeContextCurrent(window);
   glewExperimental = GL_TRUE;
   glewInit(); // Init GLEW 
   
       
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LESS);
   glfwWindowHint(GLFW_SAMPLES,4);

   const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
   printf("GLSL version: %s\n", glslVersion);
}


