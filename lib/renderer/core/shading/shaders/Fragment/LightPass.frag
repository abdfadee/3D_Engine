#version 330 core

in vec2 TexCoords;

struct Light {
    vec3 position;
    vec3 color;
    float intensity;
    float radius;
};
uniform Light light;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;
uniform sampler2D gProps;
uniform sampler2D gDepth;

out vec4 FragColor;

void main() {
    vec3 pos = vec3 (gl_FragCoord.x , gl_FragCoord.y , 0.0);
    pos.z = texture(gDepth , pos.xy).r;

    vec3 lightDir = light.position-pos;

    float dist = length(lightDir);
    float atten = 1.0 - clamp ( dist / light.radius , 0.0 , 1.0);
    if(atten == 0.0) {
        discard ;
    }

    FragColor = vec4(texture(gDepth,TexCoords).xyz,1.0);

    /*
    if (FragColor.w < 0.1)
        discard;
    */
}