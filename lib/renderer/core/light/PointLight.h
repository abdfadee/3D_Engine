#pragma once
#include "../Light.h"
#include "../Renderer.h"



class PointLight : public Light {
	float radius;

	PointLight(vec3 position , vec3 color , float radius , float intensity = 1.0f) :
	Light(position,color,intensity),
	radius(radius) {}


    void render(mat4 parentMatrix = mat4(1.0f), bool materialize = true) {
        Object3D::render(parentMatrix);
		Renderer::lights.push_back(this);
    }

};