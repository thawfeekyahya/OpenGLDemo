#version 410

in vec3 color_data;
out vec4 frag_color;

uniform vec2 u_resolution;
uniform float u_time;

vec3 colorA = vec3(1.0,0.120,0.545);
vec3 color = vec3(0.0);

float random(vec3 seed) {
    return fract(sin(dot(seed, vec3(12.9898, 78.233, 45.164))) * 43758.5453);
}

void main() {

    float randomValue = random(color_data);
    
    // Create a time offset for each face
    float phase = mod(abs(u_time) + randomValue, 1.0);

    // Define start and end colors for the transition
    vec4 startColor = vec4(color_data,1.0);
    vec4 endColor = vec4(0.5, 0.5, 0.5, 0.0)*vec4(color_data,1.0);    // Semi-transparent blue

    // Animate the transition using the random phase
    frag_color = mix(startColor, endColor, smoothstep(0.0, 1.0, phase));
    
    //float pct = sin(u_time);
    //color = mix(colorA,color_data*gl_FragCoord.z,pct);           
    //color = mix(vec3(1.0,0.0,0.0),vec3(0.0,1.0,0.0),0.5);
    //frag_color = vec4(color_data,1.0);
}
