#version 430 core

struct Light {
    vec4 color;         // rgb:color + a:intensity
    vec4 position;      // xyz:pos + w:range
    vec3 direction;
    vec2 cutOff;        // x:inner + y:outer
    float type;
};

layout(std430, binding = 1) buffer LightBuffer {
    Light lights[];
};


vec3 processDirectionalLight (Light light, vec3 viewDirection);
vec3 processPointLight (Light light, vec3 viewDirection);
vec3 processSpotLight (Light light, vec3 viewDirection);


in vec3 Normal;
in vec2 TexCoord;
in vec3 WorldPos;
in mat3 TBN;


struct Material {
    vec4 color;
    float shininess;
    sampler2D diffuseMap;
    sampler2D speculerMap;
};
uniform Material material;

uniform int lightsNum;
uniform vec3 viewPos;


out vec4 FragColor;


void main() {
    /*
    vec3 viewDir = normalize(viewPos-WorldPos);
    vec3 result = vec3(0.0);
    
    for (int i = 0 ; i<lightsNum ; ++i)
        result += processDirectionalLight(lights[i],viewDir);

    FragColor = vec4(result,1.0);

    if (FragColor.w < 0.1)
        discard;
    */

    FragColor = vec4(1.0f);
}



vec3 processDirectionalLight (Light light, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);
    vec3 halfwayDir = normalize(lightDir + viewDir);

    // Ambient
    vec3 ambient = light.color.rgb * 0.2 * (material.color + texture(material.diffuseMap,TexCoord)).xyz;

    // Difuse
    float diff = max(dot(Normal,lightDir),0.0);
    vec3 diffuse = light.color.rgb * diff * (material.color + texture(material.diffuseMap,TexCoord)).xyz;

    // Speculer
    float spec = pow(max(dot(Normal,halfwayDir),0.0),material.shininess);
    vec3 speculer = light.color.rgb * spec * (material.color + texture(material.speculerMap,TexCoord)).xyz;

    // Result
    return (ambient + diffuse + speculer) * light.color.a;
}