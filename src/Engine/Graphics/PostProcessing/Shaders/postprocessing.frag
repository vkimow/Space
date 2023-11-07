#version 330 core

out vec4 FragColor;
in vec2 texCoords;

uniform sampler2D origin;
uniform sampler2D bloom;

void main()
{
    vec3 originFragment = texture(origin, texCoords).rgb;
    vec3 bloomFragment = texture(bloom, texCoords).rgb;
    FragColor.rgb = originFragment + bloomFragment * 3;
}