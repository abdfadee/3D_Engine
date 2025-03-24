#pragma once

#include "../shading/shaders.h"
#include "../core/object3d.h"
#include "../core/mesh.h"


class NormalVisualizerHelper : public Object3D {
	Mesh* mesh;

public:

	NormalVisualizerHelper(Mesh* mesh) : mesh(mesh) {}

	void render(mat4 parentMatrix, bool materialize = true) {
		Object3D::render(parentMatrix);

		//if (!materialize) return;

		Shaders::NormalVisualizer.use();
		Shaders::NormalVisualizer.setMat4("model", worldMatrix);
		Shaders::NormalVisualizer.setVec4("color", vec4(1.0f));

		glBindVertexArray(mesh->VAO);
		glDrawElements(GL_TRIANGLES, mesh->geometry->indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

};