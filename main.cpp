#include <iostream>
#include <sstream>
#include <string>

#include "stb_image.h"
#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "modules/include/Triangle.h"
#include "modules/include/mainwindow.h"
#include "modules/include/Log.h"
#include <chrono>

using namespace std;


int main() {

    MainWindow w;

    int isokay = w.initialize();

    if (isokay == 1) {
        cerr<<"Could not launch GLFW3A"<<endl;
        return 1;
    } 

    GLFWwindow* window =  w.createWindow(640,480,"Hello Triangle");

    if(!window) {
        cerr<<"Could not open window GLFW3 Window"<<endl;
        glfwTerminate();
        return 1;
    }

    w.makeEnv(window);

    Triangle t;    
    t.drawTriangle(window);
    
    Log l;
    l.restart_gl_log("HI","Hello",1,2,3,22.5);
    l.appendLog("now this is another message");


    int v;
    glGetIntegerv(GL_MAX_DRAW_BUFFERS,&v);
    l.appendLog("GL_MAX_DRAW_BUFFER->",v);

    glfwTerminate();


    return 0;
}

