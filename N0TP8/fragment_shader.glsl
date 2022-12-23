#version 330 core

// Output data
out vec4 FragColor;
// Ajouter une variable interpolée o_color venant du vertex shader
in vec3 o_color;

in vec2 o_uv;

uniform sampler2D texture1;

void main()
{
    // Mettre à jour la couleur avec la variable interpolée venant du vertex shader
    // FragColor = vec4(o_color, 1.);
    FragColor = texture(texture1,o_uv);
}
