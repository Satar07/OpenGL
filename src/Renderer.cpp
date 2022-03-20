#pragma once

#include "Renderer.h"
#include <iostream>


//调试用断言 true : 程序继续运行  false ： 程序中断
#define ASSERT(x) if(!(x))  __debugbreak();

//调用GL函数检查是否报错
#define GLCall(x) GLClearError(); \
	x; \
	ASSERT(GLLogCall(#x,__FILE__,__LINE__))

void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum e = glGetError()) {
		std::cout << "[OpenGL Error] (" << e << ") :" << function << " "
			<< file << ":" << line << std::endl;
		return false;
	}
	return true;
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {

	//绑定
	va.Bind();
	shader.Bind();

	GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const {
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
