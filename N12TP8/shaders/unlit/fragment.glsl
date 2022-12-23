#version 330 core

in vec3 o_positionWorld;
in vec3 o_normalWorld;
in vec3 o_uv0;
out vec4 FragColor;

uniform vec3 camera_pos;
uniform vec4 color;
uniform sampler2D colorTexture;
uniform sampler2D bumpMap;
uniform samplerCube skybox;

void main() 
{
    // FragColor = color;
    // FragColor = texture( colorTexture, o_uv0.xy ) * color;

    vec3 N = normalize(o_normalWorld);
    vec3 I = o_positionWorld - camera_pos;
    vec3 R = reflect ( I, N );
    FragColor = vec4 ( texture ( skybox, R ).rgb , 1.0);

    /*
    float du = ( texture(bumpMap, vec2(o_uv0.x+0.01, o_uv0.y)).x - texture(bumpMap, vec2(o_uv0.x-0.01, o_uv0.y)).x )/2;
    float dv = ( texture(bumpMap, vec2(o_uv0.x, o_uv0.y+0.01)).x - texture(bumpMap, vec2(o_uv0.x, o_uv0.y-0.01)).x )/2;
    vec3 diru = vec3(1, 0, du);
    vec3 dirv = vec3(0, 1, dv);
    vec3 m = diru*dirv;
    FragColor = vec4( 0.5*normalize(m) + 0.5, 1.0 ) * texture(colorTexture, o_uv0.xy);// * color;
    */

    // DEBUG: position
    // FragColor = vec4(o_positionWorld, 1.0);
    // DEBUG: normal
    // FragColor = vec4(0.5 * o_normalWorld + vec3(0.5) , 1.0);
    // DEBUG: uv0
    // FragColor = vec4(o_uv0, 1.0);
}
