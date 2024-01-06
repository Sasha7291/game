#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>

#include "../renderer/shaderprogram.h"

class ResourceManager
{
public:
	explicit ResourceManager(const std::string& path);
	~ResourceManager() = default;

	std::shared_ptr<Renderer::ShaderProgram> loadShaderProgram(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
	std::shared_ptr<Renderer::ShaderProgram> getShaderProgram(const std::string& name) const;

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;

private:
	std::string getFileText(const std::string& relativePath) const;

	typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramMap;
	ShaderProgramMap shaderPrograms;

	std::string path;
};