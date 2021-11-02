#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoord;

out vec2 TexCoord;

uniform vec2 positionOffset;

void main()
{
	gl_Position = vec4(pos.x+positionOffset.x,pos.y+positionOffset.y,pos.z,1.0);
	TexCoord = texCoord;
}

