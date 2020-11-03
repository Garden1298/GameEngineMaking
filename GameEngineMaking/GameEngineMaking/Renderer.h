#pragma once
#include <iostream>

#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h" 
#include "glm/gtc/matrix_transform.hpp"

#include "Object.h"
#include "ICleanUp.h"
#include "IRenderer.h"
//#include "RenderableObject.h"
#include "NonRenderableObject.h"
#include "ControlableObject.h"

class RenderableObject;

class Renderer : public ICleanUp
{
public:
	GLFWwindow* window;
	ControlableObject* control;

	std::vector<RenderableObject*> _renderingObject;
	std::vector<NonRenderableObject*> _nonRenderingObject;

	GLuint programID;

	static Renderer* instance()
	{
		static Renderer instance;
		return &instance;
	}

	void init();
	void render();
	void update();//렌더되지 않은 걸 업데이트 해주는 멤버함수
	void addObject(RenderableObject* src_obj);
	void addObject(NonRenderableObject* src_obj);
	virtual void shutDown() override;

	GLuint GetProgramID() { return programID; }
};
