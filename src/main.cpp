#include <Gl/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Shader.h"


int main() {
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	//�򿪴�ֱͬ��
	glfwSwapInterval(1);

	//�ڴ��ڰ�֮���ʼ��glew
	glewInit();

	//���OpenGl�汾
	std::cout << glGetString(GL_VERSION) << std::endl;

	//�����ڲ�������  Ϊ�˹رմ���ʱ�˳�����
	{
		//data  dot position  and the subsequence they draw
		float position[] = {
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.5f,  0.5f,
			-0.5f,  0.5f
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};


		//vertex array object
		VertexArray va;


		//vettex buffer obj
		VertexBuffer vb(position, 2 * 6 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		//index buffer obj
		IndexBuffer ib(indices, 6);


		//shader
		Shader shader("res/shader/Basic.shader");
		shader.Bind();


		//change color
		float r = 0.8f;
		float increment = 0.05f;

		shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);


		//unbind everything
		va.UnBind();
		vb.UnBind();
		ib.UnBind();
		shader.UnBind();

		Renderer renderer;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window)) {
			/* Render here */
			renderer.Clear();

			if (r > 1.0f)
				increment = -0.05f;
			else if (r < 0.0f)
				increment = 0.05f;
			r += increment;

			shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

			renderer.Draw(va, ib, shader);

			/* Swap front and back buffers */
			GLCall(glfwSwapBuffers(window));

			/* Poll for and process events */
			GLCall(glfwPollEvents());
		}
	}
	glfwTerminate();
	return 0;
}