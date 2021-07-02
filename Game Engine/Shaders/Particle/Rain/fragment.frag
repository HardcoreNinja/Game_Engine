#version 130

uniform float u_time;

vec3 colorA = vec3(0.889,0.883,0.912);
vec3 colorB = vec3(0.008,0.188,1.000);

void main() {
    vec3 color = vec3(0.0);

    float pct = abs(sin(u_time));

    // Mix uses pct (a value from 0-1) to
    // mix the two colors
    color = mix(colorA, colorB, pct);

    gl_FragColor = vec4(color,1.0);
}