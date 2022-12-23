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
	if (m_phong_program != 0) {
		glDeleteProgram(m_phong_program);
	}
	if (m_albedo_program != 0) {
		glDeleteProgram(m_albedo_program);
	}
	if (m_metalness_program != 0) {
		glDeleteProgram(m_metalness_program);
	}
	if (m_roughness_program != 0) {
		glDeleteProgram(m_roughness_program);
	}
	if (m_AO_program != 0) {
		glDeleteProgram(m_AO_program);
	}
}

void Material::init() 
{
	// TODO : Change shader by your
	m_program = load_shaders("shaders/unlit/vertex.glsl", "shaders/unlit/fragment.glsl");
	m_phong_program = load_shaders("shaders/unlit/vertex.glsl", "shaders/unlit/fragmentPhong.glsl");
	m_albedo_program = load_shaders("shaders/unlit/vertex.glsl", "shaders/unlit/fragmentAlbedo.glsl");
	m_metalness_program = load_shaders("shaders/unlit/vertex.glsl", "shaders/unlit/fragmentMetalness.glsl");
	m_roughness_program = load_shaders("shaders/unlit/vertex.glsl", "shaders/unlit/fragmentRoughness.glsl");
	m_AO_program = load_shaders("shaders/unlit/vertex.glsl", "shaders/unlit/fragmentAO.glsl");
	check();
	cur_material = 0;
	// TODO : set initial parameters
	m_color = {1.0, 1.0, 1.0, 1.0};
	m_texture = loadTexture2DFromFilePath("WaterBottleTexture.png");
	m_metalnessmap = loadTexture2DFromFilePath("metalnessmap2.png");
	m_roughnessmap = loadTexture2DFromFilePath("metalnessmap2.png");
	m_AOmap = loadTexture2DFromFilePath("AOmap2.png");
}

void Material::clear() {
	// nothing to clear
	// TODO: Add the texture or buffer you want to destroy for your material
	glDeleteTextures(1, (GLuint*) &m_texture);
	glDeleteTextures(1, (GLuint*) &m_metalnessmap);
	glDeleteTextures(1, (GLuint*) &m_roughnessmap);
	glDeleteTextures(1, (GLuint*) &m_AOmap);
}

void Material::bind() {
	check();

	cur_program = m_program;
	if( cur_material == phong ) cur_program = m_phong_program;
	else if( cur_material == albedo ) cur_program = m_albedo_program;
	else if( cur_material == metalness ) cur_program = m_metalness_program;
	else if( cur_material == roughness ) cur_program = m_roughness_program;
	else if( cur_material == AO ) cur_program = m_AO_program;

	// std::cout << cur_material << ", " << cur_program << '\n';

	glUseProgram(cur_program);
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

	glm::vec3 cam_pos = Context::camera.getPosition();
	glUniform3f( getUniform("camera_pos"), cam_pos[0], cam_pos[1], cam_pos[2] );

	if( cur_material != none )
	{
		glUniform3f( getUniform("lightPos"), lightPos[0], lightPos[1], lightPos[2] );
		glUniform3f( getUniform("lightColor"), lightCol[0], lightCol[1], lightCol[2] );

		glm::vec3 ambient, specular, diffuse;
		float shininess = 0.;

		if( cur_material == phong )
		{
			ambient = phong_ambient;
			diffuse = phong_diffuse;
			specular = phong_specular;
			shininess = phong_shininess;
		}
		else if( cur_material == albedo )
		{
			ambient = albedo_ambient;
			diffuse = albedo_diffuse;
			specular = albedo_specular;
			shininess = albedo_shininess;
		}
		else if( cur_material == metalness )
		{
			ambient = metalness_ambient;
			diffuse = metalness_diffuse_NM;
			specular = metalness_specular_NM;
			shininess = metalness_shininess_NM;

			if (m_metalnessmap != 0) 
			{
				glUniform1i(getUniform("metalnessmap"), GL_TEXTURE1);
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, m_metalnessmap);
			}
			
			glUniform3f( getUniform("freinel_val"), freinel_val[0], freinel_val[1], freinel_val[2] );
			glUniform3f( getUniform("color_non_metal"), color_non_metal[0], color_non_metal[1], color_non_metal[2] );

			glUniform3f( getUniform("metal.specular"), metalness_specular_M[0], metalness_specular_M[1], metalness_specular_M[2] );
			glUniform3f( getUniform("metal.diffuse"), metalness_diffuse_M[0], metalness_diffuse_M[1], metalness_diffuse_M[2] );
			glUniform3f( getUniform("metal.ambient"), metalness_ambient[0], metalness_ambient[1], metalness_ambient[2] );
			glUniform1f( getUniform("metal.shininess"), metalness_shininess_M);
		}
		else if( cur_material == roughness )
		{
			ambient = roughness_ambient;
			diffuse = roughness_diffuse;
			specular = roughness_specular;
			shininess = roughness_shininess;

			if (m_roughnessmap != 0) 
			{
				glUniform1i(getUniform("roughnessmap"), GL_TEXTURE1);
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, m_roughnessmap);
			}

			glUniform4f( getUniform("color"), 0., 0., 0., 1. );
		}
		else if( cur_material == AO )
		{
			ambient = AO_ambient;
			diffuse = AO_diffuse;
			specular = AO_specular;
			shininess = AO_shininess;

			if (m_AOmap != 0) 
			{
				glUniform1i(getUniform("AOmap"), GL_TEXTURE1);
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, m_AOmap);
			}
		}

		glUniform3f( getUniform("material.specular"), specular[0], specular[1], specular[2] );
		glUniform3f( getUniform("material.diffuse"), diffuse[0], diffuse[1], diffuse[2] );
		glUniform3f( getUniform("material.ambient"), ambient[0], ambient[1], ambient[2] );
		glUniform1f( getUniform("material.shininess"), shininess );
	}

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
	return glGetAttribLocation(cur_program, in_attributeName.c_str());
}

GLint Material::getUniform(const std::string& in_uniformName) {
	check();
	return glGetUniformLocation(cur_program, in_uniformName.c_str());
}
