#pragma once
#include <glm/glm.hpp>
#include "../core/light.h"


class SpotLight : public Light {
public:
	vec3 direction;
	float innerCutOff;
	float outerCutOff;
	float range;


	SpotLight(vec3 direction, vec3 color, float intensity,float range) :
		innerCutOff(cos(radians(innerCutOff))),		// cosine of cutOff angle
		outerCutOff(cos(radians(outerCutOff))),
		range(range),
		direction(direction),
		Light(color, intensity) {}


	void updateShadowMap() {

	}

};
