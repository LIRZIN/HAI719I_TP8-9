#version 330 core

in vec3 TexCoord;
out vec4 FragColor;

uniform vec3 camera_pos;
uniform vec4 color;
uniform sampler2D colorTexture;
uniform sampler2D bumpMap;
uniform samplerCube skybox;

void main() {
    vec3 I = TexCoord - camera_pos;
    vec4 ( texture ( skybox ,I  ) . rgb , 1.0) ;
    // DEBUG: position
    //FragColor = vec4(o_positionWorld, 1.0);
    // DEBUG: normal
    // FragColor = vec4(0.5 * o_normalWorld + vec3(0.5) , 1.0);
    // DEBUG: uv0
    // FragColor = vec4(o_uv0, 1.0);
}
