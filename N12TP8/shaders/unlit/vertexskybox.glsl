#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
//uniform mat4 mvp;
//uniform mat4 modelView;
//uniform mat4 normalMatrix;

out vec3 TexCoord;

void main() 
{
  TexCoord = vec3(model*vec4(position, 1.));//position;
  gl_Position = projection * view * vec4( TexCoord, 1.);
}
