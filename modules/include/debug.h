#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>

class Debug{
    public:
        Debug();
        void debug_shader(GLuint shaderIndex);
        void debug_program(GLuint program);
};

#endif //DEBUG_H
