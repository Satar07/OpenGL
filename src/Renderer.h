#pragma once

#include <Gl/glew.h>
#include <GLFW/glfw3.h>

#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"


//调试用断言 true : 程序继续运行  false ： 程序中断
#define ASSERT(x) if(!(x))  __debugbreak()

//调用GL函数检查是否报错
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