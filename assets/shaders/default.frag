#version 410

in vec3 color_data;
out vec4 frag_color;

uniform vec2 u_resolution;
uniform float u_time;

vec3 colorA = vec3(1.0,0.120,0.545);
vec3 color = vec3(0.0);

void main() {
    float pct = sin(u_time);
    color = mix(colorA,color_data*gl_FragCoord.z,pct);           
    //color = mix(vec3(1.0,0.0,0.0),vec3(0.0,1.0,0.0),0.5);
    frag_color = vec4(color,1.0);
}

