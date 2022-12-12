#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
	unsigned int id;

	Shader();
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
	void activate();

	void generate(const char* vertexShaderPath, const char* fragmentShaderPath);

	std::string loadShaderSrc(const char* filepath);
	GLuint compileShader(const char* filepath, GLenum type);

	void setMat4(const std::string& name, glm::mat4 val);
	void setInt(const std::string& name, int value);
	void setBool(const std::string& name, bool value);
	void setFloat(const std::string& name, float value);
	void set4Float(const std::string& name, float v1, float v2, float v3, float v4);

};

#endif

