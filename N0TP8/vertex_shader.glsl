#version 330 core

//A faire
// ajouter une variable uniform pour tous les sommets de type float permettant la mise à l'échelle
uniform float scale;
// ajouter une variable uniform pour tous les sommets de type vec3 permettant d'appliquer une translation au modèle
uniform vec3 translate;

uniform float time_gl;

// i.e. a appliquer sur tous les sommets
//---------

//---------
// ajouter une variable o_color de type vec3 interpolée a envoyer au fragment shader
out vec3 o_color;
out vec2 o_uv;

// Input vertex data, different for all executions of this shader. layout 0
layout(location = 0) in vec3 vertexPosition_modelspace;
// A faire : ajouter un attribut de sommet color, contenant les couleurs pour chaque sommet à ( location = 1 ) layout 1
layout(location = 1) in vec3 color;

layout(location = 2) in vec2 uv;


void main(){
    //Mettre à jour ce code pour appliquer la translation et la mise à l'échelle
    //Multiplier par scale permet de definir la mise à l'echelle
    gl_Position =  vec4(vertexPosition_modelspace*scale+translate,1);

    //Assigner la normale à la variable interpolée color

    o_color = color;

    o_color[0] = o_color[0];
    o_color[1] = o_color[1];
    o_color[2] = o_color[2];

    /*
    if(time_gl <= -0.50){
        float temp = o_color[0];
        o_color[0] = o_color[1];
        o_color[1] = o_color[2];
        o_color[2] = temp;
    }
    if (time_gl >= 0.50){
        float temp = o_color[0];
        o_color[0] = o_color[2];
        o_color[2] = o_color[1];
        o_color[1] = temp;
    }
    */

    o_uv = uv;

}

