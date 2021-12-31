#ifndef SHADER_DATA_H
#define SHADER_DATA_H

#include "GL/glew.h"
#include "GLFW/glfw3.h"

class ShaderData {
  public:
    ShaderData();
    void create(GLuint* pBuffer,GLuint* pArrayData,GLuint* IndicesData);
    GLuint getMappedArray();
  private:
    void createMemoryInGPUAndMapVertexData(GLuint* pBuffer);
    void describeDataPresentInArray(GLuint* pBuffer);
    void optimizeVertexUsingCommonIndices(GLuint* pBuffer);
};


















#endif // SHADER_DATA_H
