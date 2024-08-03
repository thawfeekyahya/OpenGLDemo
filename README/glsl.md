## GLSL Versioning

1. OpenGL 1.2 - no GLSL
2. OpenGL 2.0 - GLSL 1.10.59 #version 110
3. OpenGL 2.1 - GLSL 1.20.08 #version 120
4. OpenGL 3.0 - GLSL 1.30.10 #version 130
5. OpenGL 3.1 - GLSL 1.40.08 #version 140
6. OpenGL 3.3 - GLSL 1.50.11 #version 150
7. OpenGL 3.3 - GLSL 3.30.06 #version 330
8. OpenGL 4.0 - GLSL 4.00.09 #version 400
9. OpenGL 4.1 - GLSL 4.10.06 #version 410
10. OpenGL 4.2 - GLSL 4.20.06 #version 420
11. OpenGL 4.3 - GLSL 4.30.06 #version 430


## GLSL types

void - functions do not return value
bool - boolean
int  - singed int
float - floating point
vec3 - 3d floating point value
vec4 - 4d floating point value
mat3 - 3x3 floting point matrix
mat4 - 4x4 floating point matrix
sampler2D - 2d texture loaded from image
samplerCube - 6 sided key-box texture
sampler2DShadow - shadow projected onto a texture

## GLSL functions

### gl_Position

```
in vec3 vertex_pos;
gl_Position = vec4(vertex_pos,1.0); 

```  

In OpenGL, **gl_Position** sets the clip space position of each vertex. The vertex data is stored in vertex buffers, which are blocks of memory on the GPU. These buffers are populated with data by the CPU and then transferred to the GPU. The vertex shader executes for each vertex in the vertex buffer, using this data to compute the final position of each vertex in clip space.


## GLSL Keywords

### in keyword
**in vec3 vertex_pos** the **in** variables are called pre-vertex attributes.

### out keyword

**out vec4 frag_color** the **out** variable used to pass variable from one stage to the next stage in the shader pipeline

### uniform keyword

The `uniform` keyword indicates that a variable is being sent to the shader program from the CPU. This variable will be globally accessible to all shaders within the program.


### Fragment Shader

The hardware knows that the first vec4 it gets as the ouput from the fragment shader should be the color of the fragment


