#version 330 core

in vec2 texCoords;

out vec4 FragColor;

uniform sampler2D source;
uniform float level;

float max3(const vec3 v) {
    return max(v.x, max(v.y, v.z));
}

vec3 box4x4(vec3 s0, vec3 s1, vec3 s2, vec3 s3) {
    return (s0 + s1 + s2 + s3) * 0.25;
}

vec3 box4x4Reinhard(vec3 s0, vec3 s1, vec3 s2, vec3 s3) {
    float w0 = 1.0 / (1.0 + max3(s0));
    float w1 = 1.0 / (1.0 + max3(s1));
    float w2 = 1.0 / (1.0 + max3(s2));
    float w3 = 1.0 / (1.0 + max3(s3));
    return (s0 * w0 + s1 * w1 + s2 * w2 + s3 * w3) * (1.0 / (w0 + w1 + w2 + w3));
}

void main() {
    vec3 c = textureLod(source, texCoords, level).rgb;

    vec3 lt  = textureLodOffset(source, texCoords, level, ivec2(-1, -1)).rgb;
    vec3 rt  = textureLodOffset(source, texCoords, level, ivec2( 1, -1)).rgb;
    vec3 rb  = textureLodOffset(source, texCoords, level, ivec2( 1,  1)).rgb;
    vec3 lb  = textureLodOffset(source, texCoords, level, ivec2(-1,  1)).rgb;

    vec3 lt2 = textureLodOffset(source, texCoords, level, ivec2(-2, -2)).rgb;
    vec3 rt2 = textureLodOffset(source, texCoords, level, ivec2( 2, -2)).rgb;
    vec3 rb2 = textureLodOffset(source, texCoords, level, ivec2( 2,  2)).rgb;
    vec3 lb2 = textureLodOffset(source, texCoords, level, ivec2(-2,  2)).rgb;

    vec3 l   = textureLodOffset(source, texCoords, level, ivec2(-2,  0)).rgb;
    vec3 t   = textureLodOffset(source, texCoords, level, ivec2( 0, -2)).rgb;
    vec3 r   = textureLodOffset(source, texCoords, level, ivec2( 2,  0)).rgb;
    vec3 b   = textureLodOffset(source, texCoords, level, ivec2( 0,  2)).rgb;

    vec3 c0, c1;

    if (level <= 0.5) {
        c0  = box4x4Reinhard(lt, rt, rb, lb);
        c1  = box4x4Reinhard(c, l, t, lt2);
        c1 += box4x4Reinhard(c, r, t, rt2);
        c1 += box4x4Reinhard(c, r, b, rb2);
        c1 += box4x4Reinhard(c, l, b, lb2);
    } else {
        c0  = box4x4(lt, rt, rb, lb);
        c1  = box4x4(c, l, t, lt2);
        c1 += box4x4(c, r, t, rt2);
        c1 += box4x4(c, r, b, rb2);
        c1 += box4x4(c, l, b, lb2);
    }

    FragColor.rgb = c0 * 0.5 + c1 * 0.125;
}
