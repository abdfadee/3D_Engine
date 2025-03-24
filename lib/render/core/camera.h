#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "object3d.h";
#include "../shading/shaders.h"
#include "../shading/ubo.h";
#include "../utility/controls.h"


using namespace glm;


class Camera : public Object3D {
public:
	UBO cameraBuffer;
	mat4 view, projection;
	vec3 cameraFront = vec3(0, 0, -1), cameraUp = vec3(0, -1, 0);
	double pre_xpos, pre_ypos;
	float sensetivity;


	Camera(float sensetivity = 0.1f) :
		cameraBuffer(UBO(0, 32 * sizeof(float))),
		sensetivity(sensetivity) {
		view = lookAt(positionVector, positionVector + cameraFront, cameraUp);
	}


	void movement(GLFWwindow* window, float deltaTime) {
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			translate(deltaTime * cameraFront);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			translate(-deltaTime * cameraFront);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			translate(-normalize(cross(cameraFront, cameraUp)) * deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			translate(normalize(cross(cameraFront, cameraUp)) * deltaTime);
	}

	void look(double xpos, double ypos) {
		static bool firstTime = true;
		if (firstTime) {
			pre_xpos = xpos;
			pre_ypos = ypos;
			firstTime = false;
		}

		double xoffset = (xpos - pre_xpos) * sensetivity;
		double yoffset = (ypos - pre_ypos) * sensetivity;

		rotate(vec3(yoffset, 0, 0));
		rotate(vec3(0,xoffset,0));

		if (rotationVector.x > 89.0f)
			setRotation(vec3(89.0f,rotationVector.y,rotationVector.z));
		else if (rotationVector.x < -89.0f)
			setRotation(vec3(-89.0f, rotationVector.y, rotationVector.z));

		pre_xpos = xpos;
		pre_ypos = ypos;
	}

	virtual void attachControls() {
		Controls::mouseListener.addListener([&](double xpos, double ypos) {look(xpos, ypos); });
		Controls::addCallback([&](GLFWwindow* window, float delta) {movement(window, delta); });
	}

	void link(mat4 parentMatrix) {
		Object3D::link(parentMatrix);

		mat3 directionMatrix = transpose(inverse(mat3(worldMatrix)));
		cameraFront = normalize(directionMatrix * vec3(0,0,-1));
		cameraUp = normalize(directionMatrix * vec3(0,-1,0));

		vec4 p = worldMatrix * vec4(0.0f, 0.0f, 0.0f, 1.0f);
		vec3 position = vec3(p) / p.w;

		view = lookAt(position, position + cameraFront, cameraUp);
	}

	void upload() {
		CameraBuffer buffer{ view,projection };
		cameraBuffer.upload(0, sizeof(buffer), &buffer);
	}


	struct CameraBuffer {
		mat4 view, projection;
	};

};