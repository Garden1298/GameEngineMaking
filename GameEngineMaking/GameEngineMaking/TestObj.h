#pragma once

#include "RenderableObject.h"
#include "Object.h"

class TestObj: public RenderableObject
{
public:
	virtual void shutdown() override;
	virtual void update() override;
};

