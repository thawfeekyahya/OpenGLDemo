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


  GLfloat vertices[] = {
    0.0f, 0.5f, 0.0f,   //Top
    0.05f, -0.5f, 0.0f, //Right
    -0.05f, -0.5f, 0.0f //Left
  };

  GLuint vbo,vao; //vertex buffer object
  
  glGenBuffers(1,&vbo);
  glBindBuffer(GL_ARRAY_BUFFER,vbo);
  glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,NULL);
  glEnableVertexAttribArray(0);

  //Main Loop

   while (!glfwWindowShouldClose(pWindow)) {
    showFPS(pWindow);
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES,0,3);
    glBindVertexArray(0);

    glfwSwapBuffers(pWindow);
  }

  glfwTerminate();
  return 0;
	
}


