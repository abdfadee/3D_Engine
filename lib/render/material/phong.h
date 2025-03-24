#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include "../core/texture.h"
#include "../core/material.h"
#include "../shading/shaders.h"


using namespace glm;


class MeshPhongMaterial : public Material {
	vec4 color;
	Texture* diffuseMap;
	Texture* speculerMap;
	float shininess;

public:
	MeshPhongMaterial(float shininess , vec4 color = vec4(0.0), Texture* diffuseMap = NULL , Texture* speculerMap = NULL) : diffuseMap(diffuseMap), speculerMap(speculerMap), color(color) {}


	void bind() {
		Shaders::Phong.use();
		Shaders::Phong.setFloat("material.shininess",shininess);

		if (diffuseMap != NULL) {
			Shaders::Phong.setInt("material.diffuseMap",0);
			Shaders::Phong.setInt("material.speculerMap", 1);
			diffuseMap->bind();
			if (speculerMap != NULL) {
				speculerMap->bind(1);
			}
			else
				diffuseMap->bind(1);
		}
		else
			Shaders::Phong.setVec4("material.color", color);
	}

};