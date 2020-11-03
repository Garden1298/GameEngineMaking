#include "RenderableObject.h"
#include <iostream>

void RenderableObject::shutDown()
{
	//Object::shutDown();

	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
	glDeleteBuffers(1, &elementbuffer);
	glDeleteTextures(1, &Texture);
	glDeleteVertexArrays(1, &VertexArrayID);
}

void RenderableObject::setPosition(glm::vec3 position)
{
	modelMatrix = glm::mat4(1.0f);
	glm::mat4 translate = glm::mat4(1.0f);

	translate = glm::translate(translate, position);

	modelMatrix = translate * modelMatrix;

	std::cout << position.x<<position.y<<position.z<< std::endl;
}