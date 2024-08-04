

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "square.h"
#include "debug.h"

Square::Square() {

}


void Square::drawSquare(GLFWwindow* window) {

    GLfloat points[] = {
       -0.5,0.5,0.0,
       -0.5,-0.5,0.0,
        0.5,-0.5,0.0,
        
        -0.5,0.5,0.0,
        0.5,0.5,0.0,
        0.5,-0.5,0.0
    };
    
    GLfloat colors[] = {
        1.0,0.0,0.0,
        0.0,1.0,0.0,
        0.0,0.0,1.0,
        
        1.0,0.0,0.0,
        0.0,1.0,0.0,
        0.0,0.0,1.0
    };
    
    const char* vertex_shader = R"(
        #version 410
        layout(location = 0) in vec3 vp;
        layout(location = 1) in vec3 color;
        out vec3 color_data;
        void main() {
            color_data = color;
            gl_Position = vec4(vp.x,vp.y,vp.z,1.0);
        };
    )";

    const char* frag_shader = R"(
        #version 410
        in vec3 color_data;
        out vec4 frag_color;
        void main() {
            frag_color = vec4(color_data,1.0);
        };
    )";


    //Generate and bind vertex data
    GLuint vbo;
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(points),points,GL_STATIC_DRAW);
   

    //Assign vertex data to vertex attribute object
    vao = 0;
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,NULL);
    
    //Generate and bind color data
    GLuint color_vbo;
    glGenBuffers(1,&color_vbo);
    glBindBuffer(GL_ARRAY_BUFFER,color_vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(colors),colors,GL_STATIC_DRAW);
    
    //Assign color data to vertex array object
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,NULL);
    
    

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs,1,&vertex_shader,NULL),
    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs,1,&frag_shader,NULL);
    glCompileShader(fs);

    Debug d;
    d.debug_shader(fs);

    shader_program = glCreateProgram();

    glAttachShader(shader_program,fs);
    glAttachShader(shader_program,vs);

    glLinkProgram(shader_program);
    
}


void Square::loop() {
    glUseProgram(shader_program);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES,0,6);
}
