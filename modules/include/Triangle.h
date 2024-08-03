#ifndef TRIANGLE_H
#define TRIANGLE_H

class GLFWwidnow;

class Triangle {
    public:
        Triangle();
        void drawTriangle(GLFWwindow* window);
        void loopTriangle();
    private:
    	GLuint shader_program; // This is important for future references and uniform locactions
    	GLuint vs;
    	GLuint fs;
    	GLuint vbo = 0;
    	GLuint vao = 0;
};

#endif //TRIANGLE_H
