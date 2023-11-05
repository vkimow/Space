#version 450

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 norm;
layout (location = 2) in vec2 tex;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform mat4 ViewProjection;

out vec3 FragNormal;
out vec3 FragPos;

void main()
{
    mat3 NormalMatrix = transpose(inverse(mat3(Model)));
    FragNormal = normalize(NormalMatrix * norm);
    vec4 WorldModel = Model * vec4(pos, 1.0);
    FragPos = vec3(WorldModel);
    gl_Position = ViewProjection * WorldModel;
}