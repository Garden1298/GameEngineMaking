#pragma once

#include "NonRenderableObject.h"

class NonRenderSample : public NonRenderableObject
{
public:
	virtual void shutDown() override;
	virtual void update() override;
};

