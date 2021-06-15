#include <iostream>
#include <sstream>

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

//-----------------Global Properites

const char* APP_TITLE = "Introduction to Modern OpenGL";
const int gWindowWidth=800;
const int gWindowHeight=600;
bool gFullScreen = false;
GLFWwindow* pWindow = NULL;

const GLchar* vertexShaderSrc = 
"#version 330 core\n"
"layout (location = 0) in vec3 pos;"
"layout (location = 1) in vec3 color;"
"out vec3 vert_color;"
"void main()"
"{"
" vert_color = color;"
" gl_Position = vec4(pos.x,pos.y,pos.z,1.0);"
"}";

const GLchar* fragmentShaderSrc = 
"#version 330 core \n"
"out vec4 frag_color;"
"in vec3 vert_color;"
"void main()"
"{"
" frag_color = vec4(vert_color,1.0f);"
"}";

//--------------Function protos

void glfw_onKey(GLFWwindow* window,int key,int scancode,int action,int mode);
bool initOpenGL();
void showFPS(GLFWwindow* window);

//--------------------------------------

bool initOpenGL() {
  
  if(!glfwInit()) {
		std::cerr<<"GLFW Intialization failed"<<std::endl;
		return false;
	}

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
  glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);

  

  if(gFullScreen) {
    GLFWmonitor* pMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* pVmode  = glfwGetVideoMode(pMonitor);

    if( pVmode != NULL) {
      pWindow = glfwCreateWindow(pVmode->width,pVmode->height,APP_TITLE,pMonitor,NULL);
    }

  } else {
    pWindow = glfwCreateWindow(gWindowWidth,gWindowHeight,APP_TITLE,NULL,NULL);
  }


  if(pWindow == NULL) {
    std::cerr << "Failed to create GLFW window " << std::endl;
    glfwTerminate();
    return false;
  }

  glfwMakeContextCurrent(pWindow);

  glfwSetKeyCallback(pWindow,glfw_onKey);

  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK ) {
    std::cerr << "GLEW Failed " << std::endl;
    return false;
  } 

  glClearColor(0.23f,0.38f,0.47f,1.0f);

  return true;
}


void glfw_onKey(GLFWwindow* window,int key,int scancode,int action,int mode){
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
     glfwSetWindowShouldClose(window,GL_TRUE);
  }
}

void showFPS(GLFWwindow* window) {
   static double previousSeconds = 0.0;
   static int frameCount = 0;
   double elapsedSeconds;
   double currentSeconds = glfwGetTime(); // reutrn number of seconds since GLFW started as a double

   elapsedSeconds = currentSeconds - previousSeconds;

   // limit text update 4 times per second
   if(elapsedSeconds > 0.25) {
     previousSeconds = currentSeconds;
     double fps = (double)frameCount / elapsedSeconds;
     double msPerFrame = 1000.0 / fps;

     std::ostringstream outs;
     outs.precision(3);
     outs << std::fixed
          << APP_TITLE << "   "
          <<"FPS" << fps << "  "
          <<"Frame Time:" << msPerFrame << " (ms)";
     glfwSetWindowTitle(window,outs.str().c_str());

     frameCount = 0;
   }
   frameCount++;
}

int main() {

  if (!initOpenGL()) {
    std::cerr << " GLFW intialization failed"<<std::endl;
    return -1;
  }

  /* 
  Vertices and Color in single vertex buffer object
  GLfloat vertices[] = {
    // pos1 pos1 pos3 is x y and z and pos4 pos5 pos6 is RGB
    0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   //Top
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,//Right
    -0.5f, -0.5f, 0.0f, 0.0f,0.0f, 1.0f //Left
  };
  */
  //Triangle position
  GLfloat vert_pos[] = {
    0.0f,0.5f,0.0f,   //Top
    0.5f,-0.5f,0.0f,  //Right
    -0.5f,-0.5f,0.0f  //Left
  };

  //Triangle color
  GLfloat vert_color[] = {
    1.0f,0.0f,0.0f,
    0.0f,1.0f,0.0f,
    0.0f,0.0f,1.0f
  };

  GLuint vbo,vbo2,vao; //vertex buffer object
  
  glGenBuffers(1,&vbo);
  glBindBuffer(GL_ARRAY_BUFFER,vbo);
  glBufferData(GL_ARRAY_BUFFER,sizeof(vert_pos),vert_pos,GL_STATIC_DRAW);

  glGenBuffers(1,&vbo2);
  glBindBuffer(GL_ARRAY_BUFFER,vbo2);
  glBufferData(GL_ARRAY_BUFFER,sizeof(vert_color),vert_color,GL_STATIC_DRAW);

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  //Position Attribute
  glBindBuffer(GL_ARRAY_BUFFER,vbo);
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,NULL);
  glEnableVertexAttribArray(0);

  //Color Attribute
  glBindBuffer(GL_ARRAY_BUFFER,vbo2);
  glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,NULL);
  glEnableVertexAttribArray(1);


  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs,1,&vertexShaderSrc,NULL);
  glCompileShader(vs);

  GLint results;
  GLchar infoLog[512];

  glGetShaderiv(vs,GL_COMPILE_STATUS, &results);
  if(!results) {
    glGetShaderInfoLog(vs,sizeof(infoLog),NULL,infoLog);
    std::cout<<" Error! Vertex sharder failed to compile"<<infoLog<<std::endl;
  }


  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs,1,&fragmentShaderSrc,NULL);
  glCompileShader(fs);

   glGetShaderiv(fs,GL_COMPILE_STATUS, &results);
  if(!results) {
    glGetShaderInfoLog(vs,sizeof(infoLog),NULL,infoLog);
    std::cout<<" Error! Fragment sharder failed to compile"<<infoLog<<std::endl;
  }


  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram,vs);
  glAttachShader(shaderProgram,fs);
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram,GL_LINK_STATUS,&results);
  if(!results) {
    glGetProgramInfoLog(shaderProgram,sizeof(infoLog),NULL,infoLog);
    std::cout<< "Error! Shader Program linker failure" <<infoLog<<std::endl;
  }

  glDeleteShader(vs);
  glDeleteShader(fs);

  //Main Loop

   while (!glfwWindowShouldClose(pWindow)) {
    showFPS(pWindow);
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES,0,3);
    glBindVertexArray(0);

    glfwSwapBuffers(pWindow);
  }

  glDeleteProgram(shaderProgram);
  glDeleteVertexArrays(1,&vao);
  glDeleteBuffers(1,&vbo);

  glfwTerminate();
  return 0;
	
}


