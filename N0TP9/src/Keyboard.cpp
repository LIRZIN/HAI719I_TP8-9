#include "Keyboard.h"
#include "Context.h"
// GLUT includes
#include <GL/glut.h>

void key (unsigned char keyPressed, int x, int y) {
	switch (keyPressed) {
		case 'f':
		if (Context::fullScreen == true) {
			glutReshapeWindow (SCREENWIDTH, SCREENHEIGHT);
			Context::fullScreen = false;
		} else {
			glutFullScreen ();
			Context::fullScreen = true;
		}
		break;


		case 'w':
		GLint polygonMode[2];
		glGetIntegerv(GL_POLYGON_MODE, polygonMode);
		if(polygonMode[0] != GL_FILL)
		glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
		else
		glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
		break;

		case '+': //Press + key to increase scale
		// scale += 0.005;
		for (int i = 0; i < Context::instances.size(); ++i) 
		{
			Instance& inst = Context::instances[i];
			Material* material = inst.material;
			material->cur_material = (material->cur_material+1)%(material->nb_materials);
		}
		break;

		case '-': //Press - key to decrease scale
		for (int i = 0; i < Context::instances.size(); ++i) 
		{
			Instance& inst = Context::instances[i];
			Material* material = inst.material;
			material->cur_material--;
			if( material->cur_material < 0 )
				material->cur_material = material->nb_materials - 1;
		}
		break;

		default:
		break;
	}
	idle ();
}
