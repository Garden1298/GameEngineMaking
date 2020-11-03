#pragma once
#include "RenderableObject.h"

class Sphere : public RenderableObject
{
public:

	virtual void shutDown() override;
	virtual void render() override;
};

