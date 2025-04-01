#include <iostream>
#include <chrono>
#include <thread>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "lib/renderer/core/initiliaze.h"
#include "lib/renderer/core/renderer.h"
#include "lib/renderer/core/view/PerspectiveCamera.h"
#include "lib/renderer/core/geometry/BoxGeometry.h"
#include "lib/renderer/helper/NormalVisualizerHelper.h"
#include "lib/renderer/core/texture/Texture.h"



int main() {
	GLFWwindow* window = initGL(800, 800);
	Renderer renderer = Renderer(window,800,800);
	Controls::initiliaze(window);


	Texture* t = new Texture{"assets/2D/brickwall.jpg"};

	Object3D* space = new Object3D{};

	Mesh* r = new Mesh{
		new BoxGeometry{1,1,1},
		new Material{vec3(1.0f,0,0),0.5f,0.0f,0.0f}
	};
	r->translate(vec3(0,0,-4));
	space->add(r);

	//NormalVisualizerHelper* helper = new NormalVisualizerHelper{r};
	//r->add(helper);


	PerspectiveCamera* camera = new PerspectiveCamera{};
	camera->attachControls();
	space->add(camera);


	auto animationLoop = [&]() {
		//space->translate(vec3(0.02,0,0));
		//space->rotate(vec3(0, 0.1,0));
		r->rotate(vec3(0, 0.1, 0));
		//camera.rotate(vec3(0, 0.001,0));
		//space->scale(vec3(1.001));
		renderer.render(space,camera);
	};

	renderer.setAnimationLoop(animationLoop);
}