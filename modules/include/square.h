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
};
#endif //SQUARE_H
