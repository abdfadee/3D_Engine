#version 430 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;

uniform mat4 model;
layout(std140,binding = 0) uniform CameraBuffer {
    mat4 view;
    mat4 projection;
};

out GEO_IN {
    mat4 projection;
    vec3 normal;
} geoIn ;


void main() {
    gl_Position = view * model * vec4(aPosition,1.0);
    geoIn.normal = vec3(transpose(inverse(view * model)) * vec4(aNormal, 0.0));
    geoIn.projection = projection;
}