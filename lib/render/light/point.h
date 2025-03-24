#pragma once
#include <glm/glm.hpp>
#include "../core/light.h"


class PointLight : public Light {
public:
	float range;

	PointLight(vec3 color, float intensity , float range) :
		range(range),
		Light(color,intensity) {}


	void updateShadowMap() {

	}

};