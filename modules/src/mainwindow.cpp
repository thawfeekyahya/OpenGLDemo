
#include "mainwindow.h"

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <string>
#include <iostream>

using namespace std;

MainWindow::MainWindow() {

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
   glewInit();
   
       
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LESS);
   glfwWindowHint(GLFW_SAMPLES,4);
}


