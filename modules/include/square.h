#ifndef SQUARE_H
#define SQUARE_H

class GLFWwindow;

class Square {
    public:
       Square();
       void drawSquare(GLFWwindow* window);
       void loop();

    private:
       GLuint vao;
       GLuint shader_program;


       float speed = 1.0f;
       float lastPos = 0.0f;

       int matrix_location;

       GLfloat matrix[16] =  {
    	  1.0f,0.0f,0.0f,0.0f,
    	  0.0f,1.0f,0.0f,0.0f,
    	  0.0f,0.0f,1.0f,0.0f,
    	  0.5f,0.0f,0.0f,1.0f
       };
}; 

#endif //SQUARE_H
