#include <iostream>
#include <sstream>

#include "stb_image.h"
#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

using namespace std;

void drawTriangle(GLFWwindow* window) {

    GLfloat points[] = {
        0.0f,0.5f,0.0f,
        0.5f,-0.5f,0.0f,
        -0.5f,-0.5f,0.0f
    };

    const char* vertex_shader = R"( 
        #version 410
        in vec3 vp;
        void main() {
          gl_Position = vec4(vp.x,vp.y-0.5,vp.z,1.0);
        };
        )";

    const char* frag_shader = R"(
        #version 410
        out vec4 frag_color;
        void main() {
            frag_color = vec4(0.5,0.0,0.5,1.0);
        };
    )";

    GLuint vbo = 0;
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(points),points,GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,NULL);

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs,1,&vertex_shader,NULL);
    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs,1,&frag_shader,NULL);
    glCompileShader(fs);

    GLuint shader_program = glCreateProgram();

    glAttachShader(shader_program,fs);
    glAttachShader(shader_program,vs);

    glLinkProgram(shader_program);

    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader_program);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES,0,3);
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
}

int main() {

    if (!glfwInit()) {
        cerr<<"Could not launch GLFW3A"<<endl;
        return 1;
    } 

    GLFWwindow* window = glfwCreateWindow(640,480,"Hello Traingle",NULL,NULL);

    if(!window) {
        cerr<<"Could not open window GLFW3 Window"<<endl;
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();

    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);

    //--------------------------------------------------Check-Version 
    cout<<"Renderer-> "<<renderer<<endl;
    cout<<"Supported version-> "<<version<<endl;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    drawTriangle(window);

    glfwTerminate();


    return 0;
}

