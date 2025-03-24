#version 430 core
layout(location = 0) in vec3 aPosition;
layout(location = 2) in vec2 aTexCoord;

uniform mat4 model;
layout(std140,binding = 0) uniform CameraBuffer {
    mat4 view;
    mat4 projection;
};

out vec2 TexCoord;

void main() {
    gl_Position = projection * view * model * vec4(aPosition,1.0);
    TexCoord = aTexCoord;
}