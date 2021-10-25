#include "SimpleShader.h"


 const GLchar** SimpleShader::getVertexShader(int id) {

    switch(id) {
        case 0:
        return &vertex1;
        break;
    }
}

const GLchar** SimpleShader::getFragmentShader(int id) 
{
    switch(id) {
        case 0:
        return &fragment1;
        break;
    }
   
}
