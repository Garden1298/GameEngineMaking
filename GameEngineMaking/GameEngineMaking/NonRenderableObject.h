#pragma once
#include "Object.h"
#include "IUpdater.h"

class NonRenderableObject :public Object, public IUpdater
{
public:
	virtual void shutDown() override {}
	virtual void update() override {}
};