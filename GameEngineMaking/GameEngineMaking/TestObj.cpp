#include "TestObj.h"

#include <iostream>

void TestObj::shutdown() {
	RenderableObject::shutdown();
}

void TestObj::update()
{
	std::cout << "asdf" << std::endl;
}