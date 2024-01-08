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

    void ShaderProgram::setBool(const std::string& name, const GLboolean value) const
    {
        glUniform1i(glGetUniformLocation(id, name.c_str()), static_cast<GLint>(value));
    }

    void ShaderProgram::setBoolArray(const std::string& name, const GLsizei size, const GLboolean* data) const
    {
        glUniform1iv(glGetUniformLocation(id, name.c_str()), size, reinterpret_cast<const GLint*>(data));
    }

    void ShaderProgram::setBvec2(const std::string& name, const GLboolean value1, const GLboolean value2) const
    {
        glUniform2i(glGetUniformLocation(id, name.c_str()), static_cast<GLint>(value1), static_cast<GLint>(value2));
    }

    void ShaderProgram::setBvec2Array(const std::string& name, const GLsizei size, const GLboolean* data) const
    {
        glUniform2iv(glGetUniformLocation(id, name.c_str()), size, reinterpret_cast<const GLint*>(data));
    }

    void ShaderProgram::setBvec3(const std::string& name, const GLboolean value1, const GLboolean value2, const GLboolean value3) const
    {
        glUniform3i(glGetUniformLocation(id, name.c_str()), static_cast<GLint>(value1), static_cast<GLint>(value2), static_cast<GLint>(value3));
    }

    void ShaderProgram::setBvec3Array(const std::string& name, const GLsizei size, const GLboolean* data) const
    {
        glUniform3iv(glGetUniformLocation(id, name.c_str()), size, reinterpret_cast<const GLint*>(data));
    }

    void ShaderProgram::setBvec4(const std::string& name, const GLboolean value1, const GLboolean value2, const GLboolean value3, const GLboolean value4) const
    {
        glUniform4i(glGetUniformLocation(id, name.c_str()), static_cast<GLint>(value1), static_cast<GLint>(value2), static_cast<GLint>(value3), static_cast<GLint>(value4));
    }

    void ShaderProgram::setBvec4Array(const std::string& name, const GLsizei size, const GLboolean* data) const
    {
        glUniform4iv(glGetUniformLocation(id, name.c_str()), size, reinterpret_cast<const GLint*>(data));
    }

    void ShaderProgram::setFloat(const std::string& name, const GLfloat value) const
    {
        glUniform1f(glGetUniformLocation(id, name.c_str()), value);
    }

    void ShaderProgram::setFloatArray(const std::string& name, const GLsizei size, const GLfloat* data) const
    {
        glUniform1fv(glGetUniformLocation(id, name.c_str()), size, data);
    }

    void ShaderProgram::setInt(const std::string& name, const GLint value) const
    {
        glUniform1i(glGetUniformLocation(id, name.c_str()), value);
    }

    void ShaderProgram::setIntArray(const std::string& name, const GLsizei size, const GLint* data) const
    {
        glUniform1iv(glGetUniformLocation(id, name.c_str()), size, data);
    }

    void ShaderProgram::setIvec2(const std::string& name, const GLint value1, const GLint value2) const
    {
        glUniform2i(glGetUniformLocation(id, name.c_str()), value1, value2);
    }

    void ShaderProgram::setIvec2Array(const std::string& name, const GLsizei size, const GLint* data) const
    {
        glUniform2iv(glGetUniformLocation(id, name.c_str()), size, data);
    }

    void ShaderProgram::setIvec3(const std::string& name, const GLint value1, const GLint value2, const GLint value3) const
    {
        glUniform3i(glGetUniformLocation(id, name.c_str()), value1, value2, value3);
    }

    void ShaderProgram::setIvec3Array(const std::string& name, const GLsizei size, const GLint* data) const
    {
        glUniform3iv(glGetUniformLocation(id, name.c_str()), size, data);
    }

    void ShaderProgram::setIvec4(const std::string& name, const GLint value1, const GLint value2, const GLint value3, const GLint value4) const
    {
        glUniform4i(glGetUniformLocation(id, name.c_str()), value1, value2, value3, value4);
    }

    void ShaderProgram::setIvec4Array(const std::string& name, const GLsizei size, const GLint* data) const
    {
        glUniform4iv(glGetUniformLocation(id, name.c_str()), size, data);
    }

    void ShaderProgram::setVec2(const std::string& name, const GLfloat value1, const GLfloat value2) const
    {
        glUniform2f(glGetUniformLocation(id, name.c_str()), value1, value2);
    }

    void ShaderProgram::setVec2Array(const std::string& name, const GLsizei size, const GLfloat* data) const
    {
        glUniform2fv(glGetUniformLocation(id, name.c_str()), size, data);
    }

    void ShaderProgram::setVec3(const std::string& name, const GLfloat value1, const GLfloat value2, const GLfloat value3) const
    {
        glUniform3f(glGetUniformLocation(id, name.c_str()), value1, value2, value3);
    }

    void ShaderProgram::setVec3Array(const std::string& name, const GLsizei size, const GLfloat* data) const
    {
        glUniform3fv(glGetUniformLocation(id, name.c_str()), size, data);
    }

    void ShaderProgram::setVec4(const std::string& name, const GLfloat value1, const GLfloat value2, const GLfloat value3, const GLfloat value4) const
    {
        glUniform4f(glGetUniformLocation(id, name.c_str()), value1, value2, value3, value4);
    }

    void ShaderProgram::setVec4Array(const std::string& name, const GLsizei size, const GLfloat* data) const
    {
        glUniform4fv(glGetUniformLocation(id, name.c_str()), size, data);
    }

    void ShaderProgram::setUint(const std::string& name, const GLuint value) const
    {
        glUniform1ui(glGetUniformLocation(id, name.c_str()), value);
    }

    void ShaderProgram::setUintArray(const std::string& name, const GLsizei size, const GLuint* data) const
    {
        glUniform1uiv(glGetUniformLocation(id, name.c_str()), size, data);
    }

    void ShaderProgram::setUivec2(const std::string& name, const GLuint value1, const GLuint value2) const
    {
        glUniform2ui(glGetUniformLocation(id, name.c_str()), value1, value2);
    }

    void ShaderProgram::setUivec2Array(const std::string& name, const GLsizei size, const GLuint* data) const
    {
        glUniform2uiv(glGetUniformLocation(id, name.c_str()), size, data);
    }

    void ShaderProgram::setUivec3(const std::string& name, const GLuint value1, const GLuint value2, const GLuint value3) const
    {
        glUniform3ui(glGetUniformLocation(id, name.c_str()), value1, value2, value3);
    }

    void ShaderProgram::setUivec3Array(const std::string& name, const GLsizei size, const GLuint* data) const
    {
        glUniform3uiv(glGetUniformLocation(id, name.c_str()), size, data);
    }

    void ShaderProgram::setUivec4(const std::string& name, const GLuint value1, const GLuint value2, const GLuint value3, const GLuint value4) const
    {
        glUniform4ui(glGetUniformLocation(id, name.c_str()), value1, value2, value3, value4);
    }

    void ShaderProgram::setUivec4Array(const std::string& name, const GLsizei size, const GLuint* data) const
    {
        glUniform4uiv(glGetUniformLocation(id, name.c_str()), size, data);
    }

    void ShaderProgram::setMatrix2(const std::string& name, const glm::mat2& matrix) const
    {
        glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void ShaderProgram::setMatrix2x3(const std::string& name, const glm::mat2x3& matrix) const
    {
        glUniformMatrix2x3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void ShaderProgram::setMatrix2x4(const std::string& name, const glm::mat2x4& matrix) const
    {
        glUniformMatrix2x4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void ShaderProgram::setMatrix3(const std::string& name, const glm::mat3& matrix) const
    {
        glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void ShaderProgram::setMatrix3x2(const std::string& name, const glm::mat3x2& matrix) const
    {
        glUniformMatrix3x2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void ShaderProgram::setMatrix3x4(const std::string& name, const glm::mat3x4& matrix) const
    {
        glUniformMatrix3x4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void ShaderProgram::setMatrix4(const std::string& name, const glm::mat4& matrix) const
    {
        glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void ShaderProgram::setMatrix4x2(const std::string& name, const glm::mat4x2& matrix) const
    {
        glUniformMatrix4x2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void ShaderProgram::setMatrix4x3(const std::string& name, const glm::mat4x3& matrix) const
    {
        glUniformMatrix4x3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
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

