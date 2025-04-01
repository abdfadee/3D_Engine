#pragma once
#include <glm/glm.hpp>
#include "3d/Object3d.h"

using namespace glm;

class Light : public Object3D {
	vec3 position;
	vec3 color;
	float intensity;

protected:
	Light(vec3 position, vec3 color, float intensity = 1.0f) :
		position(position),
		color(color),
		intensity(intensity) {}
};