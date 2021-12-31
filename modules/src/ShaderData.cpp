#include "ShaderData.h"

//TODO: Unable to do this in header file, find how to do this in C++
GLfloat vertices[] = {
    -0.5,  0.5, 0.0, 0.0, 0.1,
    0.5,  0.5, 0.0, 1.0, 1.0,
    0.5, -0.5, 0.0, 1.0, 0.0,
    -0.5, -0.5, 0.0, 0.0, 0.0
};

GLuint indicess []  = {
    0, 1, 2, //first triangle vertices
    0, 2, 3  //second triangle vertices
};  

ShaderData::ShaderData() 
{
  
}

void ShaderData::create(GLuint* pBufferData,GLuint* pArrayData,GLuint* pIndicesBuffer) 
{
  createMemoryInGPUAndMapVertexData(pBufferData);
  describeDataPresentInArray(pArrayData);
  optimizeVertexUsingCommonIndices(pIndicesBuffer);
}

void ShaderData::createMemoryInGPUAndMapVertexData(GLuint* pBufferData) 
{
  // Part1, Create Memory in GPU---------------------------------------------------------------------

  //Create new buffer in GPU memory and get the reference in passed parameter [bufferSpace]
  glGenBuffers(1,pBufferData); 

  //Make bufferObject active of type GL_ARRAY_BUFFER
  glBindBuffer(GL_ARRAY_BUFFER,*pBufferData);

  //Take the CPU data ( traingleVertices ) and pass it to the active buffer (based on previous step)
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices,GL_STATIC_DRAW);

}

void ShaderData::describeDataPresentInArray(GLuint* pArrayData) 
{
   //Part2 , Describe strides/data in array-----------------------------------------------------------


//This is required by core OpenGL
  int vertexId1 = 0;
  int vertexId2 = 1;
  //Generate a vertex Array in GPU and load the reference to the passed parameter
  glGenVertexArrays(1,pArrayData);
  
  //Bind this array 
  glBindVertexArray(*pArrayData);
  
  // Define the first pointer for verticies mapping
  //VertexAttribPointer is used to describe how data is laid out in the vertex array 
  // <triangleVertices> is array of 9 elements ,but its actually represented as 3 vertex point of a triange
  /**
   * @vertexID unique id and this is referenced in the fragment shader code
   * @ 3 , how many data in a stride
   * @ GL_FLOAT type of data
   * @ GL_FALSE shoudl normalize 
   * @ 5*sizeof(GLfloat) Specifies the byte offset between consecutive generic vertex attributes
   * @ NULL Specifies a offset of the first component
   * */
  glVertexAttribPointer(vertexId1,3,GL_FLOAT,GL_FALSE,5*sizeof(GLfloat),NULL);

  //enable this vertex array
  glEnableVertexAttribArray(vertexId1); 
  

  //Define the second pointer for fragment mapping
  glVertexAttribPointer(vertexId2,2,GL_FLOAT,GL_FALSE,5*sizeof(GLfloat),(GLvoid*)(3*sizeof(GLfloat)));
  glEnableVertexAttribArray(vertexId2); 

}


void ShaderData::optimizeVertexUsingCommonIndices(GLuint* pIndicesBuffer) 
{
  //Part3 , Describe indices ---------------------------------------------------------------------
  
  GLuint bufferObject;
  glGenBuffers(1,pIndicesBuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,*pIndicesBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indicess),indicess,GL_STATIC_DRAW);
}