#ifndef SQUARE_H
#define SQUARE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include "AbsShape.h"

class GLFWwindow;

class Square : public AbsShape {
    public:
       Square();
       void draw(GLFWwindow* window) override;
       void loop() override;

    private:
       GLuint vao;
       GLuint shader_program;

       int mvp_location; // Model View Location from GLSL

       float speed = 1.0f;
       float lastPos = 0.0f;
        
       // Projection Matrix-------------------------------------------------------------
       //Field of view
       //Screen ratio
       //Z far and Z near 
       float viewAngle=glm::radians(45.0f),aspect=640/480,nearDist=1.00f,farDist=50.0f;
       //-------------------------------------------------------------------------------

       glm::mat4 view;
       glm::mat4 model;
       glm::mat4 proj;
       glm::mat4 mvp = glm::mat4(1.0f);
}; 

#endif //SQUARE_H
