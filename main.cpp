#include <iostream>
#include <chrono>
#include <thread>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "lib/render/core/initiliaze.h"
#include "lib/render/core/renderer.h"
#include "lib/render/geometry/rectangle.h"
#include "lib/render/geometry/box.h"
#include "lib/render/helper/normalvisualizer.h"
#include "lib/render/core/texture.h"
#include "lib/render/material/basic.h"
#include "lib/render/material/phong.h"
#include "lib/render/camera/perspective.h"
#include "lib/render/light/directional.h"



int main() {
	Renderer renderer = Renderer{};


	Texture* t = new Texture{"assets/2D/brickwall.jpg"};

	Object3D* space = new Object3D{};

	Mesh* r = new Mesh{
		new BoxGeometry{1,1,1},
		//new MeshBasicMaterial{vec4(1.0f,0,0,1.0f),t}
		new MeshPhongMaterial{64.0f,vec4(1.0f,0.0f,0.0f,0.0f)}
	};
	r->translate(vec3(0,0,-4));
	space->add(r);

	NormalVisualizerHelper* helper = new NormalVisualizerHelper{r};
	r->add(helper);


	PerspectiveCamera* camera = new PerspectiveCamera{};
	camera->attachControls();
	space->add(camera);


	DirectionalLight l = DirectionalLight{
	vec3(0,-1,0),
	vec3(1.0f),
	1.0f
	};


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