#include <iostream>
#include <windows.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "IndexBuffer.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

const static std::string s_squareShapeFilePath = "res/json/square.json";
const static std::string s_avatarFilePath = "res/avatar2.jpg";

int main(void)
{
	// Initialise GLFW
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		system("pause");
		return -1;
	}

	//Setup GLFW

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	// Open a window and create its OpenGL context
	GLFWwindow* window = glfwCreateWindow(1024, 768, "Karakass", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		glfwTerminate();
		system("pause");
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		system("pause");
		return -1;
	}

	std::cout << "Using GL Version: " << glGetString(GL_VERSION) << std::endl;

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	{
		float vertices[] =
		{
			// position          // uv

			-1.f, -1.f, 0.f,     0.f, 0.f,
			 1.f, -1.f, 0.f,     1.f, 0.f,
			 1.f,  1.f, 0.f,     1.f, 1.f,
			-1.f,  1.f, 0.f,     0.f, 1.f
		};

		unsigned int indices[] =
		{
			0, 1, 2,
			2, 3, 0
		};

		VertexArray va;
		VertexBuffer vb(vertices, sizeof(vertices));
		IndexBuffer ib(indices, 6);

		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		//matrices transformation
		glm::mat4 proj = glm::ortho(-14.0, 14.0, -10.5, 1.5, -1.0, 1.0);

		//Shader setup
		Shader shaderBasic;
		//shaderBasic.SetUniformMat4f("u_mvp", proj);
		

		//Texture
		Texture texture(s_avatarFilePath);
		texture.Bind(0);
		//need to match the texture bind arg passed
		//shaderBasic.SetUniform1i("u_texture", 0);

		Renderer renderer;

		double time = glfwGetTime();

		while (!glfwWindowShouldClose(window))
		{
			/*shaderBasic.Bind();
			shaderBasic.SetUniform1f("u_time", time);
			//shaderBasic.SetUniform2f("u_spectrum", 1.0f, 0.0f);
			shaderBasic.Unbind();
			// Clear the screen
			renderer.Clear();
			renderer.Draw(va, ib, shaderBasic);

			// Swap buffers
			GLCall(glfwSwapBuffers(window));
			GLCall(glfwPollEvents());

			time = glfwGetTime();*/

			//----------

			renderer.Clear();
			renderer.Draw(va, ib, shaderBasic);

			float timeValue = (float)glfwGetTime();

			shaderBasic.Bind();
			shaderBasic.SetUniform1f("u_time", timeValue);
			//shaderBasic.SetUniform2f("u_spectrum", 1.0f, 0.0f);
			shaderBasic.Unbind();

			// Clear the screen
			renderer.Clear();
			renderer.Draw(va, ib, shaderBasic);

			// Swap buffers
			GLCall(glfwSwapBuffers(window));
			GLCall(glfwPollEvents());
		}

		ib.Unbind();
		va.Unbind();
		vb.Unbind();
		shaderBasic.Unbind();
		texture.Unbind();

		// Cleanup VBO
		GLCall(glDeleteVertexArrays(1, &VertexArrayID));
	}
	

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
	system("pause");
	return 0;
}