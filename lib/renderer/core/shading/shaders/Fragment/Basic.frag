#version 430 core

in vec2 TexCoords;

uniform vec4 color;
uniform sampler2D diffuseMap;

out vec4 FragColor;

void main() {
    FragColor = color + texture(diffuseMap,TexCoords);

    
    if (FragColor.w < 0.1)
        discard;
}