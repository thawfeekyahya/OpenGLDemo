

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include "square.h"
#include "debug.h"


Square::Square() {

      
      model = glm::mat4(1.0f);

      //Projection matrix on screen
      proj = glm::perspective (viewAngle,aspect,nearDist,farDist);

      //Model matrix
      model = glm::rotate(model,glm::radians(0.0f),glm::vec3(0.0f,1.0f,0.0));

      //Camera Position
      //Camera target position
      //Camera upvector (specify which side is up)
      view = glm::lookAt( glm::vec3(0.0,0.0,3.0),glm::vec3(0.0,0.0,0.0), glm::vec3(0.0,1.0,0.0) );
}

void Square::drawSquare(GLFWwindow* window) {

    GLfloat points[] = {
       -0.5,0.5,0.0,  // Cordinates for the first triangle
       -0.5,-0.5,0.0,  
        0.5,-0.5,0.0,  
        
        -0.5,0.5,0.0, 
        0.5,0.5,0.0,  // Cordinates for the second triangle
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
        
        uniform mat4 matrix; 
        out vec3 color_data;
        
        void main() {
            color_data = color;
            gl_Position =  matrix * vec4(vp,1.0);

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
    
    
    //Get the uniform variable location from GLSL 
    matrix_location = glGetUniformLocation(shader_program,"matrix");


    
   //Assign the value from CPU (matrix) to the GPU (GLSL) variable via location
    //glUniformMatrix4fv(matrix_location,1,GL_FALSE,matrix);
    
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    //glFrontFace(GL_CW);
}


void Square::loop() {
    
    using namespace std;

    /*
    static double prev_sec = glfwGetTime();
    
    double curr_sec = glfwGetTime();
    double elapsed_sec = curr_sec - prev_sec;
    prev_sec = curr_sec;

    //if (fabs(lastPos)> 1.0f) {
       speed += 0.01; 
    //}

    double angle =  elapsed_sec * speed + lastPos;

    matrix[2][3] =  elapsed_sec * speed + lastPos;
    matrix[0][0] =  cos(speed);
    matrix[0][1] =  -sin(speed);
    matrix[1][3] =  sin(speed);
    matrix[2][2] =  cos(speed);

    lastPos = matrix[2][3];
    */
    //Camera projection
    
    mvp = proj * view * model;
    glUniformMatrix4fv(matrix_location,1,GL_FALSE,&mvp[0][0]);

   //Assign the value from CPU (matrix) to the GPU (GLSL) variable via location
   //glUniformMatrix4fv(matrix_location,1,GL_FALSE,&matrix[0][0]);

    glUseProgram(shader_program);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES,0,6);
}
