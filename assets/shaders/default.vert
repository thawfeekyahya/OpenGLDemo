#version 460 core

layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 colors;
layout(location = 2) in uint faceIndex;

uniform mat4 mvp; 

layout (std140,binding=4) uniform Colors {
  vec3 faceColors[6];
} clr;


out vec3 color_data;

void main() {
    color_data = clr.faceColors[faceIndex];
    gl_Position =   mvp * vec4(vp,1.0);
}
