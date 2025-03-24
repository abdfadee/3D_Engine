#pragma once
#include <glm/glm.hpp>
#include "object3d.h"

using namespace glm;


class Light : public Object3D {
protected:
	vec3 color;
	float intensity;

public:
	Light(vec3 color, float intensity) : color(color) , intensity(intensity) {}

	virtual void updateShadowMap() = 0;

	virtual void link(mat4 parentMatrix) = 0;
};