/**
 @file shaderprogram.h
 @author STD
 @date 08.01.2024
 @brief Объявление класса шейдерной программы
 */
#pragma once

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat2x2.hpp>
#include <glm/mat2x3.hpp>
#include <glm/mat2x4.hpp>
#include <glm/mat3x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat3x4.hpp>
#include <glm/mat4x2.hpp>
#include <glm/mat4x3.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>
#include <string>

/**
namespace Renderer
@brief Пространство имён Renderer
@details Данное пространство имён содержит все классы,
		  необходимые для рендеринга и отрисовки графики.
*/
namespace Renderer {
	/**
	@brief Класс шейдерной программы
	@details Данный класс осуществляет создание шейдерной программы и её использование 
			  во время рендеринга графики.
	*/
	class ShaderProgram
	{
	public:
		/**
		@brief Основной конструктор шейдерной программы
		@details Данный конструктор создаёт вертексный и фрагментный шейдер и
				  линкует их в шейдерную программу с определённым ID. В случае неудачи
				  выведет сообщение об ошибке.
		@param[in] vertexShader  Код вертексного шейдера
		@param[in] fragmentShader Код фрагментного шейдера
		*/
		explicit ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
		/**
		@brief Конструктор перемещения шейдерной программы
		@details Данный конструктор выполняет перемещение шейдерной программы
				  в новый объект, при этом информация о шейдерной программе в
				  предыдущем объекте затирается.
		*/
		ShaderProgram(ShaderProgram&& shaderProgram) noexcept;
		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		/**
		@brief Деструктор шейдерной программы
		*/
		~ShaderProgram();

		/**
		@brief Проверка компиляции шейдерной программы
		@return true, если шейдерная программа скомпилирована; иначе false
		*/
		bool isCompiled() const;

		/**
		@brief Сеттер значения типа bool в uniform
		@details Устанавливает значение типа bool для конкретной юниформы
				 в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] value Устанавливаемое значение
		*/
		void setBool(const std::string& name, const GLboolean value) const;
		/**
		@brief Сеттер массива значений типа bool в uniform
		@details Устанавливает массив значений типа bool для конкретной 
				 юниформы в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] size Размер буффера данных
		@param[in] data Указатель на буффер данных
		*/
		void setBoolArray(const std::string& name, const GLsizei size, const GLboolean* data) const;
		/**
		@brief Сеттер значения типа bvec2 в uniform
		@details Устанавливает значение типа bvec2 для конкретной юниформы
				 в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] value1, value2 Устанавливаемые значения
		*/
		void setBvec2(const std::string& name, const GLboolean value1, const GLboolean value2) const;
		/**
		@brief Сеттер массива значений типа bvec2 в uniform
		@details Устанавливает массив значений типа bvec2 для конкретной
				 юниформы в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] size Размер буффера данных
		@param[in] data Указатель на буффер данных
		*/
		void setBvec2Array(const std::string& name, const GLsizei size, const GLboolean* data) const;
		/**
		@brief Сеттер значения типа bvec3 в uniform
		@details Устанавливает значение типа bvec3 для конкретной юниформы
				 в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] value1, value2, value3 Устанавливаемые значения
		*/
		void setBvec3(const std::string& name, const GLboolean value1, const GLboolean value2, const GLboolean value3) const;
		/**
		@brief Сеттер массива значений типа bvec3 в uniform
		@details Устанавливает массив значений типа bvec3 для конкретной
				 юниформы в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] size Размер буффера данных
		@param[in] data Указатель на буффер данных
		*/
		void setBvec3Array(const std::string& name, const GLsizei size, const GLboolean* data) const;
		/**
		@brief Сеттер значения типа bvec4 в uniform
		@details Устанавливает значение типа bvec4 для конкретной юниформы
				 в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] value1, value2, value3, value4 Устанавливаемые значения
		*/
		void setBvec4(const std::string& name, const GLboolean value1, const GLboolean value2, const GLboolean value3, const GLboolean value4) const;
		/**
		@brief Сеттер массива значений типа bvec4 в uniform
		@details Устанавливает массив значений типа bvec4 для конкретной
				 юниформы в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] size Размер буффера данных
		@param[in] data Указатель на буффер данных
		*/
		void setBvec4Array(const std::string& name, const GLsizei size, const GLboolean* data) const;
		/**
		@brief Сеттер значения типа float в uniform
		@details Устанавливает значение типа float для конкретной юниформы
				 в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] value Устанавливаемое значение
		*/
		void setFloat(const std::string& name, const GLfloat value) const;
		/**
		@brief Сеттер массива значений типа float в uniform
		@details Устанавливает массив значений типа float для конкретной
				 юниформы в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] size Размер буффера данных
		@param[in] data Указатель на буффер данных
		*/
		void setFloatArray(const std::string& name, const GLsizei size, const GLfloat* data) const;
		/**
		@brief Сеттер массива значений типа int в uniform
		@details Устанавливает массив значений типа int для конкретной
				 юниформы в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] value Устанавливаемое значение
		*/
		void setInt(const std::string& name, const GLint value) const;
		/**
		@brief Сеттер массива значений типа int в uniform
		@details Устанавливает массив значений типа int для конкретной
				 юниформы в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] size Размер буффера данных
		@param[in] data Указатель на буффер данных
		*/
		void setIntArray(const std::string& name, const GLsizei size, const GLint* data) const;
		/**
		@brief Сеттер массива значений типа ivec2 в uniform
		@details Устанавливает массив значений типа ivec2 для конкретной
				 юниформы в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] value1, value2 Устанавливаемые значения
		*/
		void setIvec2(const std::string& name, const GLint value1, const GLint value2) const;
		/**
		@brief Сеттер массива значений типа ivec2 в uniform
		@details Устанавливает массив значений типа ivec2 для конкретной
				 юниформы в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] size Размер буффера данных
		@param[in] data Указатель на буффер данных
		*/
		void setIvec2Array(const std::string& name, const GLsizei size, const GLint* data) const;
		/**
		@brief Сеттер массива значений типа ivec3 в uniform
		@details Устанавливает массив значений типа ivec3 для конкретной
				 юниформы в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] value1, value2, value3 Устанавливаемые значения
		*/
		void setIvec3(const std::string& name, const GLint value1, const GLint value2, const GLint value3) const;
		/**
		@brief Сеттер массива значений типа ivec3 в uniform
		@details Устанавливает массив значений типа ivec3 для конкретной
				 юниформы в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] size Размер буффера данных
		@param[in] data Указатель на буффер данных
		*/
		void setIvec3Array(const std::string& name, const GLsizei size, const GLint* data) const;
		/**
		@brief Сеттер массива значений типа ivec4 в uniform
		@details Устанавливает массив значений типа ivec4 для конкретной
				 юниформы в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] value1, value2, value3, value4 Устанавливаемые значения
		*/
		void setIvec4(const std::string& name, const GLint value1, const GLint value2, const GLint value3, const GLint value4) const;
		/**
		@brief Сеттер массива значений типа ivec4 в uniform
		@details Устанавливает массив значений типа ivec4 для конкретной
				 юниформы в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] size Размер буффера данных
		@param[in] data Указатель на буффер данных
		*/
		void setIvec4Array(const std::string& name, const GLsizei size, const GLint* data) const;
		/**
		@brief Сеттер значения типа vec2 в uniform
		@details Устанавливает значение типа vec2 для конкретной юниформы
				 в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] value1, value2 Устанавливаемые значения
		*/
		void setVec2(const std::string& name, const GLfloat value1, const GLfloat value2) const;
		/**
		@brief Сеттер массива значений типа vec2 в uniform
		@details Устанавливает массив значений типа vec2 для конкретной
				 юниформы в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] size Размер буффера данных
		@param[in] data Указатель на буффер данных
		*/
		void setVec2Array(const std::string& name, const GLsizei size, const GLfloat* data) const;
		/**
		@brief Сеттер значения типа vec3 в uniform
		@details Устанавливает значение типа vec3 для конкретной юниформы
				 в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] value1, value2, value3 Устанавливаемые значения
		*/
		void setVec3(const std::string& name, const GLfloat value1, const GLfloat value2, const GLfloat value3) const;
		/**
		@brief Сеттер массива значений типа vec3 в uniform
		@details Устанавливает массив значений типа vec3 для конкретной
				 юниформы в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] size Размер буффера данных
		@param[in] data Указатель на буффер данных
		*/
		void setVec3Array(const std::string& name, const GLsizei size, const GLfloat* data) const;
		/**
		@brief Сеттер значения типа vec4 в uniform
		@details Устанавливает значение типа vec4 для конкретной юниформы
				 в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] value1, value2, value3, value4 Устанавливаемые значения
		*/
		void setVec4(const std::string& name, const GLfloat value1, const GLfloat value2, const GLfloat value3, const GLfloat value4) const;
		/**
		@brief Сеттер массива значений типа vec4 в uniform
		@details Устанавливает массив значений типа vec4 для конкретной
				 юниформы в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] size Размер буффера данных
		@param[in] data Указатель на буффер данных
		*/
		void setVec4Array(const std::string& name, const GLsizei size, const GLfloat* data) const;
		/**
		@brief Сеттер значения типа uint в uniform
		@details Устанавливает значение типа uint для конкретной юниформы
				 в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] value Устанавливаемое значение
		*/
		void setUint(const std::string& name, const GLuint value) const;
		/**
		@brief Сеттер массива значений типа uint в uniform
		@details Устанавливает массив значений типа uint для конкретной
				 юниформы в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] size Размер буффера данных
		@param[in] data Указатель на буффер данных
		*/
		void setUintArray(const std::string& name, const GLsizei size, const GLuint* data) const;
		/**
		@brief Сеттер значения типа uivec2 в uniform
		@details Устанавливает значение типа uivec2 для конкретной юниформы
				 в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] value1, value2 Устанавливаемые значения
		*/
		void setUivec2(const std::string& name, const GLuint value1, const GLuint value2) const;
		/**
		@brief Сеттер массива значений типа uivec2 в uniform
		@details Устанавливает массив значений типа uivec2 для конкретной
				 юниформы в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] size Размер буффера данных
		@param[in] data Указатель на буффер данных
		*/
		void setUivec2Array(const std::string& name, const GLsizei size, const GLuint* data) const;
		/**
		@brief Сеттер значения типа uivec3 в uniform
		@details Устанавливает значение типа uivec3 для конкретной юниформы
				 в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] value1, value2, value3 Устанавливаемые значения
		*/
		void setUivec3(const std::string& name, const GLuint value1, const GLuint value2, const GLuint value3) const;
		/**
		@brief Сеттер массива значений типа uivec3 в uniform
		@details Устанавливает массив значений типа uivec3 для конкретной
				 юниформы в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] size Размер буффера данных
		@param[in] data Указатель на буффер данных
		*/
		void setUivec3Array(const std::string& name, const GLsizei size, const GLuint* data) const;
		/**
		@brief Сеттер значения типа uivec4 в uniform
		@details Устанавливает значение типа uivec4 для конкретной юниформы
				 в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] value1, value2, value3, value4 Устанавливаемые значения
		*/
		void setUivec4(const std::string& name, const GLuint value1, const GLuint value2, const GLuint value3, const GLuint value4) const;
		/**
		@brief Сеттер массива значений типа uivec4 в uniform
		@details Устанавливает массив значений типа uivec4 для конкретной
				 юниформы в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] size Размер буффера данных
		@param[in] data Указатель на буффер данных
		*/
		void setUivec4Array(const std::string& name, const GLsizei size, const GLuint* data) const;
		/**
		@brief Сеттер матрицы размера 2x2 в uniform
		@details Устанавливает матрицу размера 2x2 в конкретную юниформу
				 в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] matrix Устанавливаемая матрица
		*/
		void setMatrix2(const std::string& name, const glm::mat2& matrix) const;
		/**
		@brief Сеттер матрицы размера 2x3 в uniform
		@details Устанавливает матрицу размера 2x3 в конкретную юниформу
				 в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] matrix Устанавливаемая матрица
		*/
		void setMatrix2x3(const std::string& name, const glm::mat2x3& matrix) const;
		/**
		@brief Сеттер матрицы размера 2x4 в uniform
		@details Устанавливает матрицу размера 2x4 в конкретную юниформу
				 в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] matrix Устанавливаемая матрица
		*/
		void setMatrix2x4(const std::string& name, const glm::mat2x4& matrix) const;
		/**
		@brief Сеттер матрицы размера 3x3 в uniform
		@details Устанавливает матрицу размера 3x3 в конкретную юниформу
				 в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] matrix Устанавливаемая матрица
		*/
		void setMatrix3(const std::string& name, const glm::mat3& matrix) const;
		/**
		@brief Сеттер матрицы размера 3x2 в uniform
		@details Устанавливает матрицу размера 3x2 в конкретную юниформу
				 в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] matrix Устанавливаемая матрица
		*/
		void setMatrix3x2(const std::string& name, const glm::mat3x2& matrix) const;
		/**
		@brief Сеттер матрицы размера 3x4 в uniform
		@details Устанавливает матрицу размера 3x4 в конкретную юниформу
				 в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] matrix Устанавливаемая матрица
		*/
		void setMatrix3x4(const std::string& name, const glm::mat3x4& matrix) const;
		/**
		@brief Сеттер матрицы размера 4x4 в uniform
		@details Устанавливает матрицу размера 4x4 в конкретную юниформу
				 в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] matrix Устанавливаемая матрица
		*/
		void setMatrix4(const std::string& name, const glm::mat4& matrix) const;
		/**
		@brief Сеттер матрицы размера 4x2 в uniform
		@details Устанавливает матрицу размера 4x2 в конкретную юниформу
				 в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] matrix Устанавливаемая матрица
		*/
		void setMatrix4x2(const std::string& name, const glm::mat4x2& matrix) const;
		/**
		@brief Сеттер матрицы размера 4x3 в uniform
		@details Устанавливает матрицу размера 4x3 в конкретную юниформу
				 в шейдерной программе.
		@param[in] name Имя переменной uniform
		@param[in] matrix Устанавливаемая матрица
		*/
		void setMatrix4x3(const std::string& name, const glm::mat4x3& matrix) const;

		/**
		@brief Устанавливает шейдерную программу в рендеринг
		@details Для использования шейдерной программы её необходимо подключить как 
				 часть текущего состояния рендеринга. Данная функция подключает текущую
				 шейдерную программу.
		*/
		void use() const;

		/**
		@brief Перегрузка оператора присваивания
		@details При присваивании одного объекта шейдера к другому
				 не должно происходить копирование объекта, т.к. могут
				 возникнуть проблему с управлением выделенной памятью,
				 поэтому оператор присваивания производит перемещение
				 шейдерной программы в новый объект класса.
		*/
		ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;
		ShaderProgram& operator=(const ShaderProgram&) = delete;

	private:
		/**
		@brief Создание отдельного шейдера
		@details Данная функция создаёт и компилирует шейдер (вертексный 
				 или фрагментный) из исходного кода на языке GLSL. В случае
				 Неудачной компиляции выведет сообщение об ошибке.
		@param[in] source Код шейдера
		@param[in] type Тип шейдера
		@param[out] shaderId ID созданного шейдера
		*/
		bool createShader(const std::string& source, const GLenum& type, GLuint& shaderId);

		bool compiled; //!< Флаг, хранящий состояние компиляции шейдерной программы
		GLuint id; //!< ID шейдерной программы

	};
}
