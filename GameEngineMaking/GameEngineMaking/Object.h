#pragma once
#include <vector>

#include "glm/glm.hpp"
#include "include/GL/glew.h"
#include "glm/gtc/matrix_transform.hpp"

#include "ICleanUp.h"

class Object:public ICleanUp
{
public:
	virtual ~Object() {}
};