#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "initiliaze.h"
#include "object3d.h"
#include "mesh.h"
#include "camera.h"
#include <iostream>
#include <functional>
#include "../shading/shaders.h"
#include "../utility/controls.h"
#include "../light/lighting.h"

using namespace std;


class Renderer {
public:
	inline static Lighting lighting;
	inline static Object3D* root;
	GLFWwindow* window;
	double deltaTime, currentFrameTime, lastFrameTime;
	

public:
	Renderer () : window(initGL(800, 800)) {
		Shaders::compile();
		Controls::initiliaze(window);
		lighting = Lighting(50);
		glEnable(GL_DEPTH_TEST);
	}


	void render(Object3D* root, Camera* camera) {
		/* Setup */
		lighting.lightData.clear();
		Renderer::root = root;
		root->link(mat4(1.0f));
		lighting.upload();
		camera->upload();

		/* Drawing */
		root->render(mat4(1.0f));
	}


	void setAnimationLoop(std::function<void()> animationLoop) {
		lastFrameTime = glfwGetTime();

		while (!glfwWindowShouldClose(Renderer::window)) {
			currentFrameTime = glfwGetTime();
			deltaTime = (currentFrameTime - lastFrameTime);
			lastFrameTime = currentFrameTime;

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

			Controls::processInput(deltaTime);

			animationLoop();

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		glfwDestroyWindow(window);
		glfwTerminate();
	}

};