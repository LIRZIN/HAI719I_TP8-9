// Local includes
#include "Material.h"
#include "Shader.h"
#include "Texture.h"
#include "Context.h"

// GLM includes
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// OPENGL includes
#include <GL/glew.h>
#include <GL/glut.h>

Material::~Material() {
	if (m_program != 0) {
		glDeleteProgram(m_program);
	}
	if (m_skybox_program != 0) {
		glDeleteProgram(m_skybox_program);
	}
}

void Material::init() 
{
	// TODO : Change shader by your
	m_program = load_shaders("shaders/unlit/vertex.glsl", "shaders/unlit/fragment.glsl");
	m_skybox_program = load_shaders("shaders/unlit/vertexskybox.glsl", "shaders/unlit/fragmentskybox.glsl");
	check();
	m_cur_program = m_program;
	// TODO : set initial parameters
	m_color = {1.0, 1.0, 1.0, 1.0};
	m_texture = loadTexture2DFromFilePath("gradient.png");
	m_bumpmap = loadTexture2DFromFilePath("bumpmap.png");
	std::vector<std::string> skybox_img;
	/*
	for( int i = 0; i < 6; i++ )
		skybox_img.push_back(std::string("sorbin_up.png"));
	*/
	/**/
	skybox_img.push_back(std::string("sides_skybox.png"));
	skybox_img.push_back(std::string("sides_skybox.png"));
	skybox_img.push_back(std::string("roof_skybox.png"));
	skybox_img.push_back(std::string("ground_skybox.png"));
	skybox_img.push_back(std::string("sides_skybox.png"));
	skybox_img.push_back(std::string("sides_skybox.png"));

	/*
	skybox_img.push_back(std::string("sorbin_lf.png"));
	skybox_img.push_back(std::string("sorbin_rt.png"));
	skybox_img.push_back(std::string("sorbin_up.png"));
	skybox_img.push_back(std::string("sorbin_dn.png"));
	skybox_img.push_back(std::string("sorbin_ft.png"));
	skybox_img.push_back(std::string("sorbin_bk.png"));
	*/
	m_skybox = loadCubemap( skybox_img );
}

void Material::clear() {
	// nothing to clear
	// TODO: Add the texture or buffer you want to destroy for your material
	glDeleteTextures(1, (GLuint*) &m_texture);
	glDeleteTextures(1, (GLuint*) &m_bumpmap);
	glDeleteTextures(1, (GLuint*) &m_skybox);
}

void Material::bind( GLuint program_to_use ) {
	m_cur_program = program_to_use;
	check();
	glUseProgram(m_cur_program);
	internalBind();
}

void Material::internalBind() {
	// bind parameters
	GLint color = getUniform("color");
	glUniform4fv(color, 1, glm::value_ptr(m_color));

	if (m_texture != 0) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glUniform1i(getUniform("colorTexture"), GL_TEXTURE0);
	}

	if ( m_bumpmap != 0) {
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D,  m_bumpmap);
		glUniform1i(getUniform("bumpMap"),GL_TEXTURE1);
	}

	if ( m_skybox != 0) {
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_CUBE_MAP,  m_skybox);
		glUniform1i(getUniform("skybox"),GL_TEXTURE2);
	}

	glm::vec3 cam_pos = Context::camera.getPosition();
	glUniform3f( getUniform("camera_pos"), cam_pos[0], cam_pos[1], cam_pos[2] );

	// TODO : Add your custom parameters here
}

void Material::setMatrices(glm::mat4& projectionMatrix, glm::mat4& viewMatrix, glm::mat4& modelMatrix)
{
	check();
	glUniformMatrix4fv(getUniform("projection"), 1, false, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(getUniform("view"), 1, false, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(getUniform("model"), 1, false, glm::value_ptr(modelMatrix));
}

GLint Material::getAttribute(const std::string& in_attributeName) {
	check();
	return glGetAttribLocation(m_cur_program, in_attributeName.c_str());
}

GLint Material::getUniform(const std::string& in_uniformName) {
	check();
	return glGetUniformLocation(m_cur_program, in_uniformName.c_str());
}
