#pragma once
#include <glm/glm.hpp>
#include "3d/Object3d.h"

using namespace glm;

class Light : public Object3D {
	vec3 color;
	float intensity;

protected:
	Light(vec3 color, float intensity = 1.0f) :
		color(color),
		intensity(intensity) {}

public:
	virtual void bind(Shader *shader) {
		vec3 position = vec3(worldMatrix * vec4(0.0f, 0.0f, 0.0f, 1.0f));
		shader->setVec3("light.position", position);
		shader->setVec3("light.color", color);
		shader->setFloat("light.intensity",intensity);
	}

};