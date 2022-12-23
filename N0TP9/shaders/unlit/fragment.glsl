#version 330 core

in vec3 FragPos;
in vec3 FragNormal;
in vec2 FragUV0;
in vec3 FragLightPos;
out vec4 FragColor;

uniform vec4 color;
uniform vec3 lightColor;
uniform sampler2D colorTexture;
uniform sampler2D AOmap;

struct Material
{
    vec3 ambient; 
    vec3 diffuse; 
    vec3 specular; 
    float shininess;
};
uniform Material material;

void main() 
{
    FragColor = texture(colorTexture, FragUV0) * color;
}
