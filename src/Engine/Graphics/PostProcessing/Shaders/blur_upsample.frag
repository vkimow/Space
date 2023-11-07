#version 330 core

in vec2 texCoords;

out vec4 FragColor;

uniform sampler2D source_to_upscale;
uniform sampler2D source_to_combine_with;

uniform float level;
uniform vec4 resolution;

void main() {
    const float radius = 1.0;
    vec4 d = vec4(resolution.zw, -resolution.zw) * radius;
    vec3 c0, c1;
    c0  = textureLod(source_to_upscale, texCoords + d.zw, level).rgb;
    c0 += textureLod(source_to_upscale, texCoords + d.xw, level).rgb;
    c0 += textureLod(source_to_upscale, texCoords + d.xy, level).rgb;
    c0 += textureLod(source_to_upscale, texCoords + d.zy, level).rgb;
    c0 += 4.0 * textureLod(source_to_upscale, texCoords, level).rgb;
    c1  = textureLod(source_to_upscale, texCoords + vec2(d.z,  0.0), level).rgb;
    c1 += textureLod(source_to_upscale, texCoords + vec2(0.0,  d.w), level).rgb;
    c1 += textureLod(source_to_upscale, texCoords + vec2(d.x,  0.0), level).rgb;
    c1 += textureLod(source_to_upscale, texCoords + vec2( 0.0, d.y), level).rgb;
    vec3 upscale_color = (c0 + 2.0 * c1) * (1.0 / 16.0);
    FragColor.rgb = upscale_color + texture(source_to_combine_with, texCoords).rgb;
}
