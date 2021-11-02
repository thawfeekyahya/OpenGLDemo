#version 330 core 

in vec2 TexCoord;
uniform vec4 vertColor;

out vec4 frag_color;

uniform sampler2D myTexture;


void main()
{
	frag_color = texture(myTexture,TexCoord);
}

