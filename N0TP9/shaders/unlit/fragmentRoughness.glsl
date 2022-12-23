#version 420 core

in vec3 FragPos;
in vec3 FragNormal;
in vec2 FragUV0;
in vec3 FragLightPos;
out vec4 FragColor;

uniform vec3 camera_pos;
uniform vec4 color;
uniform vec3 lightColor;
layout ( binding = 0 ) uniform sampler2D colorTexture;

struct Material
{
    vec3 ambient; 
    vec3 diffuse; 
    vec3 specular; 
    float shininess;
};
uniform Material material;

layout ( binding = 1 ) uniform sampler2D roughnessmap;

void main() 
{
    vec3 ambient = lightColor * material.ambient;

    vec3 norm = normalize( FragNormal );
    vec3 lightDir = normalize( FragLightPos - FragPos );
    float diff = max( dot( norm, lightDir), 0. );
    vec3 diffuse = lightColor * ( diff * material.diffuse );

    vec3 viewDir = normalize( -FragPos );
    vec3 reflectDir = reflect( -lightDir, norm );
    float spec = pow( max( dot( viewDir, reflectDir ), 0. ), material.shininess  );
    vec3 specular = lightColor * ( spec * material.specular )* texture( roughnessmap, FragUV0 ).r ;

    vec3 result = ( ambient + diffuse + specular );
    FragColor = vec4( result, 1. )*texture( colorTexture, FragUV0 );//+ vec4(specular, 0.);//+color;

     //FragColor = color;
    // FragColor = texture(colorTexture, o_uv0) * color;
    // DEBUG: position
    //FragColor = vec4(o_positionWorld, 1.0);
    // DEBUG: normal
    // FragColor = vec4(0.5 * o_normalWorld + vec3(0.5) , 1.0);
    // DEBUG: uv0
    // FragColor = vec4(o_uv0, 1.0);
}