#pragma once
#include <iostream>
#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Initiliaze.h"
#include "3d/Object3d.h"
#include "3d/Mesh.h"
#include "view/Camera.h"
#include "shading/shaders/Shaders.h"
#include "../utility/Controls.h"
#include "framebuffer/FrameBuffer.h"
#include "geometry/RectangleGeometry.h"
#include "Light.h"

using namespace std;


class Renderer {
public:
	GLuint width, height;
	FrameBuffer* gBuffer;
	GLFWwindow* window;
	double deltaTime, currentFrameTime, lastFrameTime;

	inline static Mesh* screen;
	inline static vector<Light*> lights;
	

public:
	Renderer (GLFWwindow* window , GLuint width , GLuint height) : 
		width(width), height(height), window(window) {
		Shaders::prepare();
		gBuffer = new FrameBuffer(width, height, 0, {
			{GL_RGB16F,GL_NEAREST,GL_CLAMP_TO_EDGE},	// Normal Buffer 
			{GL_RGB8,GL_NEAREST,GL_CLAMP_TO_EDGE},		// Color Buffer 
			{GL_RGB16F,GL_NEAREST,GL_CLAMP_TO_EDGE},	// Props Buffer 
			{GL_DEPTH_COMPONENT24,GL_NEAREST,GL_CLAMP_TO_BORDER}	// Depth Buffer
		});
		screen = new Mesh(new RectangleGeometry(2, 2));
		glViewport(0, 0, width, height);
		glEnable(GL_DEPTH_TEST);
	}


	void render(Object3D* root, Camera* camera) {
		camera->updateMatrices();


		// Geometery Pass
		gBuffer->bind();

		Shaders::GeometryShader->use();
		Shaders::GeometryShader->setInt("albedoMap", 0);
		Shaders::GeometryShader->setInt("roughnessMap", 1);
		Shaders::GeometryShader->setInt("metallicMap", 2);
		Shaders::GeometryShader->setInt("normalMap", 3);
		Shaders::GeometryShader->setInt("displacmentMap", 4);
		Shaders::GeometryShader->setInt("aoMap", 5);

		lights.clear();
		root->render(Shaders::GeometryShader);



		// Light Pass
		glBindFramebuffer(GL_FRAMEBUFFER,0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		Shaders::LightShader->use();
		camera->bind();
		Shaders::LightShader->setVec2("pixelSize",vec2(1.0f / width, 1.0f / height));
		Shaders::LightShader->setInt("gNormal", 0);
		Shaders::LightShader->setInt("gAlbedo", 1);
		Shaders::LightShader->setInt("gProps", 2);
		Shaders::LightShader->setInt("gDepth", 3);

		for (int i = 0; i < gBuffer->buffers.size() ; ++i) {
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, gBuffer->buffers[i]);
		}

		for (int i = 0; i < lights.size(); ++i) {
			lights[i]->bind(Shaders::LightShader);
		}

		//screen->render(mat4(1.0f),false);

	}


	void setAnimationLoop(std::function<void()> animationLoop) {
		lastFrameTime = glfwGetTime();

		while (!glfwWindowShouldClose(Renderer::window)) {
			currentFrameTime = glfwGetTime();
			deltaTime = (currentFrameTime - lastFrameTime);
			lastFrameTime = currentFrameTime;

			Controls::processInput(deltaTime);

			animationLoop();

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		glfwDestroyWindow(window);
		glfwTerminate();
	}


};