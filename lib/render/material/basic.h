#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include "../core/texture.h"
#include "../core/material.h"
#include "../shading/shaders.h"


using namespace glm;


class MeshBasicMaterial : public Material {
private:
	Texture* diffuseMap;
	vec4 color;


public:
	MeshBasicMaterial(vec4 color = vec4(0.0), Texture* diffuseMap = NULL) : diffuseMap(diffuseMap), color(color) {}

	void bind() {
		Shaders::Basic.use();

		if (diffuseMap != NULL) {
			diffuseMap->bind();
		}
		else {
			Shaders::Basic.setVec4("color", color);
		}
	}

};