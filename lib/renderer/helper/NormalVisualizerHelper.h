#pragma once

#include "../core/shading/shaders/Shaders.h"
#include "../core/3d/Object3d.h"
#include "../core/3d/Mesh.h"


class NormalVisualizerHelper : public Object3D {
	Mesh* mesh;

public:

	NormalVisualizerHelper(Mesh* mesh) : mesh(mesh) {}

	void render(mat4 parentMatrix, bool materialize = true) {
		Object3D::render(NULL,parentMatrix);

		//if (!materialize) return;

		Shaders::NormalVisualizer->use();
		Shaders::NormalVisualizer->setMat4("model", worldMatrix);
		Shaders::NormalVisualizer->setVec4("color", vec4(1.0f));

		glBindVertexArray(mesh->VAO);
		glDrawElements(GL_TRIANGLES, mesh->geometry->indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

};