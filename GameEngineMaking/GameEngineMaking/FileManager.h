#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

#include "include/GL/glew.h"
#include "glm/gtc/matrix_transform.hpp"

#include "Object.h"
#include "RenderableObject.h"
#include "Renderer.h"

using namespace std;

class FileManager
{
public:
	FileManager() {}

	//╫л╠шео фпео
	static FileManager* instance()
	{
		static FileManager instance;
		return &instance;
	}

	void loadObj(
		RenderableObject* target_obj,
		std::string obj_path,
		std::string texture_path,
		std::string vs_shader_path,
		std::string fs_shader_path,
		Renderer* render_obj);

	bool loadOBJ(
		const char* path,
		std::vector<glm::vec3>& out_vertices,
		std::vector<glm::vec2>& out_uvs,
		std::vector<glm::vec3>& out_normals);

	GLuint loadDDS(const char* imagepath);
	GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);

	struct PackedVertex {
		glm::vec3 position;
		glm::vec2 uv;
		glm::vec3 normal;
		bool operator<(const PackedVertex that) const {
			return memcmp((void*)this, (void*)&that, sizeof(PackedVertex)) > 0;
		};
	};

	bool getSimilarVertexIndex_fast(
		PackedVertex& packed,
		std::map<PackedVertex, unsigned short>& VertexToOutIndex,
		unsigned short& result);

	void indexVBO(
		std::vector<glm::vec3>& in_vertices,
		std::vector<glm::vec2>& in_uvs,
		std::vector<glm::vec3>& in_normals,

		std::vector<unsigned short>& out_indices,
		std::vector<glm::vec3>& out_vertices,
		std::vector<glm::vec2>& out_uvs,
		std::vector<glm::vec3>& out_normals);

	vector<string> csv_read_row(istream& _file, char delimiter);
	void loadCSVFile(const string _fileName, GLfloat* array);
};

