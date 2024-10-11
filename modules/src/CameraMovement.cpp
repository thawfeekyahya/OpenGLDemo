
#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include "debug.h"
#include "shaderLoader.h"
#include "CameraMovement.h" 

CameraMovement::CameraMovement() {

      
      windowSize = glm::vec2(640,480);


      model = glm::mat4(1.0f);

      glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.5f));
      // Apply the translation to the model matrix
      
      model = translation * model;

      //Projection matrix on screen
      proj = glm::perspective (viewAngle,aspect,nearDist,farDist);


      //Camera Position
      //Camera target position
      //Camera upvector (specify which side is up)
      // 3X3 Matrix
      view = glm::lookAt( 
             glm::vec3(0.0,0.0,3.0),
             glm::vec3(0.0,0.0,0.0),
             glm::vec3(0.0,1.0,0.0) 
         );
}

void CameraMovement::draw(GLFWwindow* window) {

    mWindow = window;
    GLfloat points[] = {
	    
       -0.5,0.5,0.0,  // Cordinates for the A triangle
       -0.5,-0.5,0.0,  
        0.5,-0.5,0.0,  
        
        -0.5,0.5,0.0, 
        0.5,0.5,0.0,  // Cordinates for the B triangle
        0.5,-0.5,0.0,

        
        0.5,-0.5,0.0,  
        0.5,-0.5,1.0,  // Cordinates for the C triangle
        0.5,0.5,1.0,  
        
        0.5,-0.5,0.0, 
        0.5,0.5,0.0,  // Cordinates for the D triangle
        0.5,0.5,1.0,
	
       -0.5,0.5,1.0,  // Cordinates for the E triangle
        0.5,0.5,1.0,  
       -0.5,0.5,0.0,  
        
        -0.5,0.5,0.0, 
        0.5,0.5,0.0,  // Cordinates for the F triangle
        0.5,0.5,1.0,
		
       -0.5,-0.5,0.0,  // Cordinates for the G triangle
       -0.5,0.5,0.0,  
       -0.5,0.5,1.0,  
        
        -0.5,-0.5,1.0, 
        -0.5,0.5,1.0,  // Cordinates for the H triangle
        -0.5,-0.5,0.0,

       -0.5,-0.5,0.0,  // Cordinates for the I triangle
       0.5,-0.5,0.0,  
       0.5,-0.5,1.0,  
        
        0.5,-0.5,1.0, 
       -0.5,-0.5,1.0,  // Cordinates for the J triangle
       -0.5,-0.5,0.0,
		
       -0.5,0.5,1.0,  // Cordinates for the K triangle
       -0.5,-0.5,1.0,  
        0.5,-0.5,1.0,  
        
        -0.5,0.5,1.0, 
        0.5,0.5,1.0,  // Cordinates for the L triangle
        0.5,-0.5,1.0
    };



    GLfloat colors[] = {

        1.0,0.0,0.0,
        1.0,0.0,0.0,
        1.0,0.0,0.0,
        
        1.0,0.0,0.0,
        1.0,0.0,0.0,
        1.0,0.0,0.0,

        
        0.0,1.0,0.0,
        0.0,1.0,0.0,
        0.0,1.0,0.0,
        
        0.0,1.0,0.0,
        0.0,1.0,0.0,
        0.0,1.0,0.0,

        0.0,0.0,1.0,
        0.0,0.0,1.0,
        0.0,0.0,1.0,
        
        0.0,0.0,1.0,
        0.0,0.0,1.0,
        0.0,0.0,1.0,

        1.0,1.0,0.0,
        1.0,1.0,0.0,
        1.0,1.0,0.0,
        
        1.0,1.0,0.0,
        1.0,1.0,0.0,
        1.0,1.0,0.0,

        1.0,0.0,1.0,
        1.0,0.0,1.0,
        1.0,0.0,1.0,
        
        1.0,0.0,1.0,
        1.0,0.0,1.0,
        1.0,0.0,1.0,

        0.0,1.0,1.0,
        0.0,1.0,1.0,
        0.0,1.0,1.0,
        
        0.0,1.0,1.0,
        0.0,1.0,1.0,
        0.0,1.0,1.0
    };
    

    ShaderLoader loader("assets/shaders/default.vert");

    string v_shader = loader.getData();
    const char* vertex_shader = v_shader.c_str();

    loader.clear();

    loader.setFilePath("assets/shaders/default.frag");
    string f_shader = loader.getData();

    const char* frag_shader = f_shader.c_str();
    
    
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
    
    
    Debug d;

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs,1,&vertex_shader,NULL),
    glCompileShader(vs);

    d.debug_shader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs,1,&frag_shader,NULL);
    glCompileShader(fs);

    d.debug_shader(fs);

    shader_program = glCreateProgram();

    glAttachShader(shader_program,fs);
    glAttachShader(shader_program,vs);

    glLinkProgram(shader_program);
    
    
    //Get the uniform variable location from GLSL 
    mvp_location = glGetUniformLocation(shader_program,"mvp");

    resolution_location = glGetUniformLocation(shader_program,"u_resolution");
    time_location = glGetUniformLocation(shader_program,"u_time");
    




    // Culling configs for performance optimization 
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    //glFrontFace(GL_CW);
}


void CameraMovement::loop() {
    
    using namespace std;

    
    static GLfloat prev_sec = glfwGetTime();
    
    GLfloat curr_sec = glfwGetTime();
    GLfloat elapsed_sec = curr_sec - prev_sec;
    prev_sec = curr_sec;


    totalTime += elapsed_sec;


    double angle =  elapsed_sec * speed + lastPos;


    //Camera projection
     //Model matrix
//    model = glm::rotate(model,glm::radians(0.5f),glm::vec3(0.5f,1.0f,0.0));
     //view  = glm::rotate(model,glm::radians(0.0f),glm::vec3(1.0f,1.0f,1.0));

    handleKeyboard(mWindow);
    
    mvp = proj * view * model;
    glUniformMatrix4fv(mvp_location,1,GL_FALSE,&mvp[0][0]);

    
    glUniformMatrix2fv(resolution_location,2,GL_FALSE,&windowSize[0]);


    glUniform1f(time_location,totalTime);

   
    glUseProgram(shader_program);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES,0,36);
}



void CameraMovement::handleKeyboard(GLFWwindow* window) {

	if (glfwGetKey(window,GLFW_KEY_LEFT)) {
            model = glm::rotate(model,glm::radians(speed),glm::vec3(0.0f,-1.0f,0.0));
	}

	if (glfwGetKey(window,GLFW_KEY_RIGHT)) {
            model = glm::rotate(model,glm::radians(speed),glm::vec3(0.0f,1.0f,0.0));
	}

	if (glfwGetKey(window,GLFW_KEY_UP)) {
            model = glm::rotate(model,glm::radians(speed),glm::vec3(-1.0f,0.0f,0.0));
	}
	
	if (glfwGetKey(window,GLFW_KEY_DOWN)) {
            model = glm::rotate(model,glm::radians(speed),glm::vec3(1.0f,0.0f,0.0));
	}
}
