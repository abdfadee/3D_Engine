#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 aBitangent;

out vec3 Normal;
out vec2 TexCoord;
out vec3 WorldPos;
out mat3 TBN;

uniform mat4 model;
uniform mat3 normalMatrix;
layout(std140) uniform CameraBuffer {
    mat4 view;
    mat4 projection;
};

void main()
{
    TexCoord = aTexCoord;
    WorldPos = vec3(model * vec4(aPos, 1.0));
    Normal = normalMatrix * aNormal;   

    vec3 T = normalize(normalMatrix * aTangent);
    vec3 B = normalize(normalMatrix * aBitangent);
    vec3 N = normalize(Normal);
    TBN = mat3(T, B, N);

    gl_Position =  projection * view * vec4(WorldPos, 1.0);
}