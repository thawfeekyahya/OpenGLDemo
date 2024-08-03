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


