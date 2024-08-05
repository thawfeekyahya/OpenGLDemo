# OpenGL

OpenGL is not a library itself; instead, it is a specification of APIs. These APIs must be implemented by GPU hardware manufacturers.

### GLuint

The Graphics Library `unsigned int` is simply a binding on top of the standard `unsigned int`, ensuring compatibility across different operating systems. Nearly everything in OpenGL is associated with a corresponding `GLuint` ID.

### Buffers

In OpenGL, buffers are chunks of memory managed by the OpenGL library. To create a buffer, you can use `glGenBuffers(ENUM_TYPE, uint to bind)`.

```

GLfloat points[] = {
    0.0f,0.5f,0.0f,
    0.5f,-0.5f,0.0f,
    -0.5f,-0.5f,0.0f
};

GLuint vbo = 0;
glGenBuffers(1,&vbo) // 1 buffer object is generated and assigned to vbo

glBindBuffer(GL_ARRAY_BUFFER,vbo); // Bind the buffer to the current context

glBufferData(GL_ARRAY_BUFFER,sizeof(points),points,GL_STATIC_DRAW);//assign previously created data to the current array buffer.

```


### Vertex attribute objects

Vertex Attribute Objects (VAOs) in OpenGL are objects that encapsulate the *state needed to specify vertex attributes*.

They store the configuration required to describe how vertex data is stored in Vertex Buffer Objects (VBOs) and how this data is fed to the vertex shader.

VAOs make it easier to manage multiple vertex attribute configurations and switch between them efficiently.

### GL's state machine

The GL operates based on a state machine, so setting a state can affect globally in the program

In Open state can be mainly divided into 3 categories

1. binding  ( for buffers of data )
2. enabling ( for rendering mode )
3. using    ( for shaders programmes)



### Shader functions

1. glCreateShader() -> create a variable for storing a shader's code in openGL , returns GLuint index to it.

2. glShaderSource() -> copy shader code from C string.

3. glCompileShader() -> compile shader

4. glGetShaderiv() -> used to check error in the shader program (iv stands for 'integer vector') , in which the results returned might be an array of values

5. glShaderInfoLog() -> creates a string with any error information

6. glDeleteShader() -> free memory used by an OpenGL shader.

7. glCreateProgram() -> create a variable for storing a combined shader program

8. glAttachShader() -> attach a compiled shader

9. glLinkProgram() -> link a shader program to active context

10. glValidateProgram() -> check if program is ready to execute.

11. glGetProgramiv() -> check for error in the program .

12. glGetProgramInfoLog() -> writes any information from link

13. glUseProgram - switch to drawing with a specified program

14. glGetActiveAttrib() -> get details of a numbered per-vertex attribute used in shader.

15. glGetAttribLocation() -> get the unique "location
"

16. glGetUniformLocation -> get the unique location of a named uniform variable

17. glGetActiveUniform() -> get details of a named uniform varible used in the shader

18. glUniform{1234}{ifd}() -> set the value of a uniform varaible 

19. glUniform{1234}{ifd}v -> set the value of a uniform varible by passing in array of values

20. glUniformMatrix{1234}{fd}v() -> set the value of a uniform matrix of 2x2 , 3x3 and 4x4 

### Interpolation

In OpenGL when we send the data from one shader pipeline to the next the values are going to be interpolated between the vertices, so the fragments between each vertices going to get different values based on their position. If we wanted to have a constant value we need to use **uniform** variables for that.


### Culling functions

1. glEnable(GL_CULL_FACE)
2. glCullFace(GL_BACK)
3. glFrontFace(GL_CW)


