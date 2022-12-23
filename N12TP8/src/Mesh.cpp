#include "Mesh.h"
// OPENGL includes
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>

Mesh::Mesh(): mNumVertices(0), mNumFaces(0), positionsBuffer(0),
normalsBuffer(0), tangentsBuffer(0), uv0Buffer(0), elementsBuffer(0) {

}

Mesh::~Mesh() {
	clear();
}
void Mesh::draw() {
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, positionsBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, normalsBuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, tangentsBuffer);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, uv0Buffer);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);// 3 because assimp 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementsBuffer);
	glDrawElements(GL_TRIANGLES, 3 * mNumFaces, GL_UNSIGNED_INT, (void*)0);
}

void Mesh::draw_skybox()  
{
	int NumFaces = 6;
	float skyboxVertices[] = {
    // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
    };

	for( int i = 0; i < NumFaces*2*3*3; i++ )
		skyboxVertices[i] *= 3000.;

	GLuint skyboxbuffer;
	glGenBuffers( 1, &skyboxbuffer );
    glBindBuffer( GL_ARRAY_BUFFER, skyboxbuffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(float)*NumFaces*2*3*3, &(skyboxVertices[0]), GL_STATIC_DRAW );

    GLuint skyboxarray;
    glGenVertexArrays(1, &skyboxarray);
    glBindVertexArray(skyboxarray);
    glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,skyboxbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	
    glColor3f( 1., 1., 1. );
	glDrawArrays( GL_TRIANGLES, 0, NumFaces*2*3 );
    // glDepthMask(GL_TRUE);

    glDeleteBuffers( 1, &skyboxbuffer );
}


void Mesh::clear() {
	if (positionsBuffer != 0) {
		glDeleteBuffers(1, &positionsBuffer);
	}
	if (normalsBuffer != 0) {
		glDeleteBuffers(1, &normalsBuffer);
	}
	if (tangentsBuffer != 0) {
		glDeleteBuffers(1, &tangentsBuffer);
	}
	if (uv0Buffer != 0) {
		glDeleteBuffers(1, &uv0Buffer);
	}
	if (elementsBuffer != 0) {
		glDeleteBuffers(1, &elementsBuffer);
	}
}
