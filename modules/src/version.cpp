#ifndef VERSION_H
#define VERSION_H
#include <iostream>
#include <sstream>


#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

using namespace std;


class Version {
    public:
      Version();

};

Version::Version() {

    if (!glfwInit()) {
        cerr<<"Could not launch GLFW3A"<<endl;
    } 

    GLFWwindow* window = glfwCreateWindow(640,480,"Hello Traingle",NULL,NULL);

    if(!window) {
        cerr<<"Could not open window GLFW3 Window"<<endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();

    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);

    //--------------------------------------------------Check-Version 
    cout<<"Renderer-> "<<renderer<<endl;
    cout<<"Supported version-> "<<version<<endl;


    glfwTerminate();

}
#endif // VERSION_H
