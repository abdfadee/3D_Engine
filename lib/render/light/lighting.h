#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "../shading/ssbo.h"

using namespace glm;
using namespace std;


struct LightData {
    vec4 color;         // rgb:color + a:intensity
    vec4 position;      // xyz:pos + w:range
    vec3 direction;
    vec2 cutOff;        // x:inner + y:outer
    float type;
};


class Lighting {
public:
    SSBO lightBuffer;
    vector<LightData> lightData;

    Lighting() {}

    Lighting(unsigned int maxLights) : lightBuffer(1,maxLights*sizeof(LightData)) {}

    void upload() {
        lightBuffer.upload(0, lightData.size() * sizeof(LightData), lightData.data());
    }

};