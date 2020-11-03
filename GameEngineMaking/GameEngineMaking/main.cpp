#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include "include/GL/glew.h"		
#include "include/GLFW/glfw3.h" 

#include "glm/glm.hpp"

#include "Object.h"
#include "RenderableObject.h"
#include "NonRenderableObject.h"
#include "Renderer.h"
#include "FileManager.h"
#include "NonRenderSample.h"
#include "ControlableObject.h"
#include "Time.h"

using namespace glm;

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "lib-vc2017/glew32.lib")
#pragma comment(lib, "lib-vc2017/glfw3.lib")
 
int main()
{
	FileManager* file_mgr = FileManager::instance();

	Renderer* renderer = Renderer::instance();
	renderer->init();

	Time* time = Time::instance();

	RenderableObject* cube = new RenderableObject();
	renderer->addObject(cube);
	cube->setPosition(glm::vec3(1.0f, 1.0f, 1.0f));

	file_mgr->loadObj(
		cube,
		"cube.obj",
		"uvtemplate.DDS",
		"vs.shader",
		"fs.shader",
		renderer);

	ControlableObject* moving_cube = new ControlableObject();

	renderer->addObject(moving_cube);
	moving_cube->setPosition(glm::vec3(1.0f, 5.0f, 1.0f));

	file_mgr->loadObj(
		moving_cube,
		"cube.obj",
		"uvtemplate.DDS",
		"vs.shader",
		"fs.shader",
		renderer);

	NonRenderSample* non_render = new NonRenderSample();
	renderer->addObject(non_render);

	while (true)
	{
		//고정
		if (time->isUpdateTiming())
		{
			renderer->update();
			moving_cube->computeMatricesFromInputs(renderer->window,moving_cube);		
		}

		//가변
		renderer->render();
	}

	renderer->shutDown();

	delete cube;
	delete non_render;
	delete moving_cube;

	return 0; 
}