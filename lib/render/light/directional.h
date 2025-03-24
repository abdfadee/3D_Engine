#pragma once
#include <glm/glm.hpp>
#include "../core/light.h"
#include "../core/renderer.h"


class DirectionalLight : public Light {
public:
	vec3 direction;


	DirectionalLight(vec3 direction, vec3 color , float intensity) :
		direction(direction), Light(color,intensity) {}


	void updateShadowMap () {
	
	}

	void link(mat4 parentMatrix) {
		Object3D::link(parentMatrix);

		mat3 directionMatrix = transpose(inverse(mat3(worldMatrix)));
		vec3 lightDirection = normalize(directionMatrix * direction);

		vec4 p = worldMatrix * vec4(0.0f, 0.0f, 0.0f, 1.0f);
		vec3 lightPosition = vec3(p) / p.w;

		Renderer::lighting.lightData.push_back(
			LightData{
				vec4(color, intensity),
				vec4(lightPosition,100.0f),
				lightDirection,
				vec2(0),
				0.0f
			}
		);
	}

};