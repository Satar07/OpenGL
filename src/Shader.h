#pragma once
#include <string>
#include <unordered_map>


struct ShaderProgramSource {
	std::string VertexSource, FragmentSource;
};

class Shader {
private:
	std::string m_FilePath;

	unsigned int m_RendererID;

	//caching for uniforms
	std::unordered_map<std::string, int> m_UniformLocationCache;

public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void UnBind() const;

	//Set Uniforms
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

private:
	int getUniformLocation(const std::string& name);

	ShaderProgramSource ParseShader(const std::string& shaderPath);

	unsigned int CreateShader(const std::string& vertaxShader, const std::string fragmentShader);

	unsigned int CompileShader(unsigned int type, const std::string& source);
};