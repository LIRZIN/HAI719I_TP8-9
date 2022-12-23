#ifndef MATERIAL_H_DEFINED
#define MATERIAL_H_DEFINED
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <stdexcept>

struct Material {
	// Shader program
	GLuint m_program;
	GLuint m_skybox_program;
	GLuint m_cur_program;

	// Material parameters
	glm::vec4 m_color;
	GLint m_texture;
	GLint m_bumpmap;
	GLint m_skybox;

	inline void check() {
		if (m_program == 0) {
			throw std::runtime_error("Shader program not initialized");
		}
		if (m_skybox_program == 0) {
			throw std::runtime_error("Skybox shader program not initialized");
		}
	}

	Material(): m_program(0), m_skybox_program(0) {

	}

	virtual ~Material();

	virtual void init();

	virtual void clear();

	void bind( GLuint m_cur_program );

	virtual void internalBind();

	void setMatrices(glm::mat4& projectionMatrix, glm::mat4& viewMatrix, glm::mat4& modelMatrix);

	GLint getAttribute(const std::string& in_attributeName);

	GLint getUniform(const std::string& in_uniformName);
};

#endif
