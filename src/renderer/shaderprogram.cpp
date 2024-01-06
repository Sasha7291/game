#include "shaderprogram.h"

namespace Renderer
{
    ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
    {
        compiled = false;
        id = 0;

        GLuint vertexShaderId = 0;
        GLuint fragmentShaderId = 0;

        if (!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderId))
        {
            std::cerr << "ERROR::Vertex shader compile time error" << std::endl;
            return;
        }
        if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderId))
        {
            std::cerr << "ERROR::Fragment shader compile time error" << std::endl;
            glDeleteShader(vertexShaderId);
            return;
        }

        id = glCreateProgram();
        glAttachShader(id, vertexShaderId);
        glAttachShader(id, fragmentShaderId);
        glLinkProgram(id);

        GLint linked = GL_TRUE;
        glGetProgramiv(id, GL_LINK_STATUS, &linked);
        if (linked == GL_FALSE)
        {
            GLchar log[1024];
            glGetProgramInfoLog(id, 1024, nullptr, log);
            std::cerr << "ERROR::Link shader time error:" << std::endl << log << std::endl;
            return;
        }
        else
        {
            compiled = true;
            glDeleteShader(vertexShaderId);
            glDeleteShader(fragmentShaderId);
        }
    }

    ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept
    {
        id = shaderProgram.id;
        compiled = shaderProgram.compiled;

        shaderProgram.compiled = false;
        shaderProgram.id = 0;
    }

    ShaderProgram::~ShaderProgram()
    {
        if (compiled)
            glDeleteProgram(id);
    }

    bool ShaderProgram::isCompiled() const
    {
        return compiled;
    }

    void ShaderProgram::use() const
    {
        glUseProgram(id);
    }

    ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram) noexcept
    {
        glDeleteProgram(id);
        id = shaderProgram.id;
        compiled = shaderProgram.compiled;

        shaderProgram.compiled = false;
        shaderProgram.id = 0;
        return *this;
    }

    bool ShaderProgram::createShader(const std::string& source, const GLenum& type, GLuint& shaderId)
    {
        shaderId = glCreateShader(type);
        const char* s = source.c_str();
        glShaderSource(shaderId, 1, &s, nullptr);
        glCompileShader(shaderId);

        GLint status = GL_TRUE;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE)
        {
            GLchar log[1024];
            glGetShaderInfoLog(shaderId, 1024, nullptr, log);
            std::cerr << "Compile shader error:" << std::endl << log << std::endl;
            return false;
        }

        return true;
    }
}
