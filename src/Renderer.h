#pragma once

#include <Gl/glew.h>
#include <GLFW/glfw3.h>

#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"


//�����ö��� true : �����������  false �� �����ж�
#define ASSERT(x) if(!(x))  __debugbreak()

//����GL��������Ƿ񱨴�
#define GLCall(x) GLClearError(); \
	x; \
	ASSERT(GLLogCall(#x,__FILE__,__LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);


class Renderer {
public:
	void Draw(const VertexArray& va,const IndexBuffer& ib,const Shader& shader) const;

	void Clear() const;

};