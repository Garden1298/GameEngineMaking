#include "Renderer.h"

void Renderer::init()
{

	//_renderingObject = new std::vector<RenderableObject*>;
	//_nonRenderingObject = new std::vector<NonRenderableObject*>;

	control = new ControlableObject;

	if (!glfwInit()) {
		std::cout << "GLFW 초기화 실패" << '\n';
		getchar();
		exit(-1);
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(
		1024, // width
		768, // height
		"GameArc_CT_Objective",
		NULL,
		NULL);

	if (!window)
	{
		std::cerr << "윈도우 생성 실패" << '\n';
		getchar();
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cerr << "GLEW 초기화 실패 " << glewGetErrorString(err) << '\n';
		getchar();
		glfwTerminate();
		exit(-1);
	}

	//ESC키 누르는 걸 확인하기 위함
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	//마우스 포인터 숨기고, 움직임 비활성화
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//마우스가 화면의 중심에 오게
	glfwPollEvents();
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);

	// Dark blue background
	glClearColor(0.2f, 0.0f, 0.4f, 0.0f);

	// depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//culling
	glEnable(GL_CULL_FACE);

}

void Renderer::render()
{
	glViewport(0, 0, 1024, 768);

	//화면 지우기
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//쉐이더 사용
	glUseProgram(programID);

	for (std::vector<RenderableObject*>::iterator iter = _renderingObject.begin(); iter != _renderingObject.end(); iter++)
	{
		glm::mat4 Projection = control->getProjectionMatrix();
		glm::mat4 View = control->getViewMatrix();

		glm::mat4 Model = (*iter)->modelMatrix;
		glm::mat4 MVP = Projection * View * Model;	//카메라 설정

		glUniformMatrix4fv((*iter)->MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv((*iter)->ModelMatrixID, 1, GL_FALSE, &Model[0][0]);
		glUniformMatrix4fv((*iter)->ViewMatrixID, 1, GL_FALSE, &View[0][0]);

		glm::vec3 lightPos = glm::vec3(0, 0, 10);
		glUniform3f((*iter)->LightID, lightPos.x, lightPos.y, lightPos.z);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, (*iter)->Texture);
		// Set our "myTextureSampler" sampler to use Texture Unit 0
		glUniform1i((*iter)->TextureID, 0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, (*iter)->vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, (*iter)->uvbuffer);
		glVertexAttribPointer(
			1,                                // attribute
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// 3rd attribute buffer : normals
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, (*iter)->normalbuffer);
		glVertexAttribPointer(
			2,                                // attribute
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// Index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*iter)->elementbuffer);

		// Draw the triangles !
		glDrawElements(
			GL_TRIANGLES,      // mode
			(*iter)->indices.size(),    // count
			GL_UNSIGNED_SHORT, // type
			(void*)0           // element array buffer offset
		);
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	// Swap buffers
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Renderer::addObject(RenderableObject* src_obj)
{
	_renderingObject.push_back(src_obj);
}

void Renderer::addObject(NonRenderableObject* src_obj)
{
	_nonRenderingObject.push_back(src_obj);
}

void Renderer::update()
{
	for (std::vector<NonRenderableObject*>::iterator iter = _nonRenderingObject.begin(); iter != _nonRenderingObject.end(); iter++)
	{
		(*iter)->update();
	}
}

void Renderer::shutDown()
{

	for (std::vector<RenderableObject*>::iterator iter = _renderingObject.begin(); iter != _renderingObject.end(); iter++)
	{
		(*iter)->shutDown();
	}

	glDeleteProgram(programID);

	delete& _renderingObject;
	delete& _nonRenderingObject;

	glfwTerminate();
}

