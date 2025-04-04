#pragma once
#include "../Light.h"
#include "../Renderer.h"
#include "../shading/Shader.h"
#include "../geometry/SpheroidGeometry.h"


class PointLight : public Light {
	float radius;
	Mesh* sphere;

public:
	PointLight(vec3 color , float radius , float intensity = 1.0f) :
	Light(color,intensity),
	radius(radius),
	sphere(new Mesh(new SpheroidGeometry(radius,radius,radius))) {}


    void render(Shader* shader, mat4 parentMatrix = mat4(1.0f), bool materialize = true) {
		Renderer::lights.push_back(this);
    }

	void bind(Shader *shader) {
		Light::bind(shader);
		shader->setFloat("light.radius", radius);
		sphere->render(shader,worldMatrix,false);
	}

};