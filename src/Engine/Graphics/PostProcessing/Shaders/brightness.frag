#version 330 core

out vec4 FragColor;

in vec2 texCoords;

uniform sampler2D image;
uniform float threshold;

void main() {
    vec3 source = texture(image, texCoords).rgb;
    FragColor.rgb = max(vec3(0.0), source - vec3(threshold));
}