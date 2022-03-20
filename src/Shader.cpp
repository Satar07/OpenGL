#include "Shader.h"
#include "Renderer.h"

#include <iostream>
#include <fstream>
#include <sstream>


Shader::Shader(const std::string& filepath)
	:m_FilePath(filepath), m_RendererID(0) {

	ShaderProgramSource shaderSource = ParseShader(filepath);
	m_RendererID = CreateShader(shaderSource.VertexSource, shaderSource.FragmentSource);
}

Shader::~Shader() {
	GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const {
	GLCall(glUseProgram(m_RendererID));
}

void Shader::UnBind() const {
	GLCall(glUseProgram(0));

}

void Shader::SetUniform1i(const std::string& name, int value) {
	Bind();
	GLCall(glUniform1i(getUniformLocation(name), value));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
	Bind();
	GLCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

int Shader::getUniformLocation(const std::string& name) {
	Bind();
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1)
		std::cerr << "Warning: Uniform " << name << " dosen't exit.\n";

	m_UniformLocationCache[name] = location;
	return location;
}



ShaderProgramSource Shader::ParseShader(const std::string& shaderPath) {
	std::ifstream fin(shaderPath);
	std::stringstream ss[2];
	std::string line;

	enum class shaderTpye {
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	shaderTpye type = shaderTpye::NONE;

	while (getline(fin, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos)
				type = shaderTpye::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = shaderTpye::FRAGMENT;
			continue;
		}
		else //text
			ss[(int)type] << line << "\n";
	}

	return { ss[0].str(),ss[1].str() };
}

unsigned int Shader::CreateShader(const std::string& vertaxShader, const std::string fragmentShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertaxShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return program;
}


//编译着色器源码
unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);


	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE) {//编译不通过
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)_malloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(id, length, &length, message));
		std::cout << "Fail to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
		std::cout << message << std::endl;

		GLCall(glDeleteProgram(id));
		return 0;
	}

	return id;
}