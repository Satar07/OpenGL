#pragma once

#include "Renderer.h"
#include <iostream>


//�����ö��� true : �����������  false �� �����ж�
#define ASSERT(x) if(!(x))  __debugbreak();

//����GL��������Ƿ񱨴�
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

	//��
	va.Bind();
	shader.Bind();

	GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const {
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
