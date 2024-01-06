#include "resourcemanager.h"

#define STBI_ONLY_PNG
#include "stb_image.h"

ResourceManager::ResourceManager(const std::string& path)
{
	size_t found = path.find_last_of("/\\");
	this->path = path.substr(0, found);
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::loadShaderProgram(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath)
{
	std::string vertexString = getFileText(vertexPath);
	if (vertexString.empty())
	{
		std::cerr << "ERROR::Vertex shader file is empty!" << std::endl;
		return nullptr;
	}
	std::string fragmentString = getFileText(fragmentPath);
	if (fragmentString.empty())
	{
		std::cerr << "ERROR::Fragment shader file is empty!" << std::endl;
		return nullptr;
	}

	std::shared_ptr<Renderer::ShaderProgram>& newShader = shaderPrograms.emplace(name, std::make_shared<Renderer::ShaderProgram>(vertexString, fragmentString)).first->second;
	if (!newShader->isCompiled())
	{
		std::cerr << "ERROR::Shader program wasn't loaded: \n" 
			<< "Vertex shader: " << vertexPath << "\n" 
			<< "Fragment shader: " << fragmentPath << std::endl;
		return nullptr;
	}
	
	return newShader;
}

std::shared_ptr<Renderer::Texture2d> ResourceManager::loadTexture(const std::string& name, const std::string& relativePath)
{
	int nChannels = 0;
	int width = 0;
	int height = 0;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* pixels = stbi_load(std::string(path + "/" + relativePath).c_str(), &width, &height, &nChannels, 0);

	if (pixels == nullptr)
	{
		std::cerr << "ERROR::Image wasn't loaded: " << path + "/" + relativePath << std::endl;
		return nullptr;
	}

	std::shared_ptr<Renderer::Texture2d> newTexture = textures.emplace(name, std::make_shared<Renderer::Texture2d>(width, 
																													height, 
																													pixels, 
																													nChannels,
																													GL_NEAREST, 
																													GL_CLAMP_TO_EDGE)).first->second;
	stbi_image_free(pixels);
	return newTexture;
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::getShaderProgram(const std::string& name) const
{
	ShaderProgramMap::const_iterator it = shaderPrograms.find(name);

	if (it == shaderPrograms.end())
	{
		std::cerr << "ERROR::Shader wasn't found!" << std::endl;
		return nullptr;
	}

	return it->second;
}

std::shared_ptr<Renderer::Texture2d> ResourceManager::getTexture(const std::string& name) const
{
	TextureMap::const_iterator it = textures.find(name);

	if (it == textures.end())
	{
		std::cerr << "ERROR::Texture wasn't found!" << std::endl;
		return nullptr;
	}

	return it->second;
}

std::string ResourceManager::getFileText(const std::string& relativePath) const
{
	std::fstream f;
	f.open(path + "/" + relativePath, std::ios::in | std::ios::binary);
	if (!f.is_open())
	{
		std::cerr << "ERROR::File wasn't opened: " << path + "/" + relativePath << std::endl;
		return std::string();
	}

	std::stringstream buffer;
	buffer << f.rdbuf();
	return buffer.str();
}
