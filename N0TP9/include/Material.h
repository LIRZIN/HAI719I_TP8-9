#ifndef MATERIAL_H_DEFINED
#define MATERIAL_H_DEFINED
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <stdexcept>

struct Material {
	// Material parameters
	glm::vec4 m_color;
	GLint m_texture;
	GLint m_metalnessmap;
	GLint m_roughnessmap;
	GLint m_AOmap;

	const int none = 0;
	GLuint m_program;

	/*
	vec3 ambient; 
    vec3 diffuse; 
    vec3 specular; 
    float shininess;
	*/

	//https://cglearn.eu/pub/advanced-computer-graphics/physically-based-shading

	// The basic Phong model
	const int phong = 1;
	const glm::vec3 phong_ambient = glm::vec3(0., 0., 0.);
	const glm::vec3 phong_diffuse = glm::vec3(1., 1., 1.);
	const glm::vec3 phong_specular = glm::vec3(0.5, 0.5, 0.5);
	const float phong_shininess = 1.;
	GLuint m_phong_program;

	// The base color of the material. For metals it defines the specular color
	const int albedo = 2;
	const glm::vec3 albedo_ambient = glm::vec3(0., 0., 0.);
	const glm::vec3 albedo_diffuse = glm::vec3(1., 1., 1.);
	const glm::vec3 albedo_specular = glm::vec3(0.5, 0.5, 0.5);
	const float albedo_shininess = 1.;
	GLuint m_albedo_program;

	// If the material is a metal or dielectric (non-metal)
	const int metalness = 3;
	const glm::vec3 metalness_ambient = glm::vec3(0.4, 0.4, 0.4);

	const glm::vec3 metalness_diffuse_NM = glm::vec3(0.05, 0.05, 0.05);
	const glm::vec3 metalness_specular_NM = glm::vec3(1, 1, 1);
	const float metalness_shininess_NM = 0.1;
	const glm::vec3 color_non_metal = glm::vec3( 0.5661, 0.3412, 0.0902 );

	const glm::vec3 metalness_diffuse_M = glm::vec3(0., 0., 0.);
	const glm::vec3 metalness_specular_M = glm::vec3(1, 1, 1);
	const float metalness_shininess_M = 3;
	const glm::vec3 freinel_val = glm::vec3(213./255., 234./255., 237./255.);
	GLuint m_metalness_program;

	// (smoothness, glossiness) – How aligned are the microfacets to the macro surface
	const int roughness = 4;
	const glm::vec3 roughness_ambient = glm::vec3(0.2, 0.2, 0.2);
	const glm::vec3 roughness_diffuse = glm::vec3(0.05, 0.05, 0.05);
	const glm::vec3 roughness_specular = glm::vec3(1., 1., 1.);
	const float roughness_shininess = 5.;
	GLuint m_roughness_program;

	const int AO = 5;
	const glm::vec3 AO_ambient = glm::vec3(0., 0., 0.);
	const glm::vec3 AO_diffuse = glm::vec3(1., 1., 1.);
	const glm::vec3 AO_specular = glm::vec3(0.5, 0.5, 0.5);
	const float AO_shininess = 1.;
	GLuint m_AO_program;

	const int nb_materials = 6;
	int cur_material = 0;
	GLuint cur_program;

	const glm::vec3 lightPos = glm::vec3(-2, 1., -1.5);
	const glm::vec3 lightCol = glm::vec3(1., 1., 1.);

	inline void check() {
		if (m_program == 0) {
			throw std::runtime_error("Shader program not initialized");
		}
		if (m_phong_program == 0) {
			throw std::runtime_error("Phong shader program not initialized");
		}
		if (m_albedo_program == 0) {
			throw std::runtime_error("Albedo shader program not initialized");
		}
		if (m_metalness_program == 0) {
			throw std::runtime_error("Metalness shader program not initialized");
		}
		if (m_roughness_program == 0) {
			throw std::runtime_error("Roughness shader program not initialized");
		}
		if (m_AO_program == 0) {
			throw std::runtime_error("AO shader program not initialized");
		}
	}

	Material(): m_program(0), m_phong_program(0), m_albedo_program(0),
	            m_metalness_program(0),m_roughness_program(0), m_AO_program(0) {}

	virtual ~Material();

	virtual void init();

	virtual void clear();

	void bind();

	virtual void internalBind();

	void setMatrices(glm::mat4& projectionMatrix, glm::mat4& viewMatrix, glm::mat4& modelMatrix);

	GLint getAttribute(const std::string& in_attributeName);

	GLint getUniform(const std::string& in_uniformName);
};

#endif
