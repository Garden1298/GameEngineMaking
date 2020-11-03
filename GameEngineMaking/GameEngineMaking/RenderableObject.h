#pragma once

#include "Object.h"
#include "IRenderer.h"

class RenderableObject :public Object, public IRenderer
{
public:
	//정점들에 대한 데이터
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	std::vector<unsigned short> indices;
	std::vector<glm::vec3> indexed_vertices;
	std::vector<glm::vec2> indexed_uvs;
	std::vector<glm::vec3> indexed_normals;

	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint normalbuffer;
	GLuint colorbuffer;//
	GLuint elementbuffer;
	
	GLuint VertexArrayID;
	//GLuint programID;
	GLuint Texture;
	GLuint TextureID;
	GLuint LightID;

	GLuint MatrixID;//뜯어질수있음
	GLuint ModelMatrixID;//뜯어질수있음
	GLuint ViewMatrixID;//뜯어질수있음

	glm::mat4 modelMatrix;

	virtual void shutDown()override;
	virtual void render()override{};
	void setPosition(glm::vec3 position);
};
