#include "Vertex.h"


#if defined __linux__ || defined WIN32
	#include <GL/gl.h>
	#include <GL/glu.h>
#elif defined __APPLE__
	#include <gl.h>
	#include <glu.h>
#endif


using namespace std;
using namespace qglviewer;

Vertex::Vertex()
	 :
	 lnum( -1 ),
	 diffuse( 0.8, 0.8, 0.8 ),
   specular(0.0, 0.0, 0.0 )
{
	 normal.setValue(0, 0, 0);
	 normalsurf.setValue(0, 0, 0);
	 lnum = -1;
	 isspecial = false;
}

// Vertex(const POINT& p)
// {
// 	 for (int i = 0; i < 3; ++i)
// 	 {
// 			position[i] = p[i];
// 			positionCour[i] = p[i];
// 			normal[i] = 0.0f;
// 	 }
// }

Vertex::Vertex(const Vec& p)
	 :
	 lnum( -1 ),
	 diffuse( 0.8, 0.8, 0.8 ),
   specular(0.0, 0.0, 0.0 )
{
	 position = p;
	 posSkinnee = p;
	 positionCour = p;
	 normal.setValue(0, 0, 0);
	 normalsurf.setValue(0, 0, 0);
	 selected = false;
	 inalimb = false;
	 lnum = -1; 
	 isspecial = false;
}

void
Vertex::draw() const
{
   
    // /TODELETE
     //glNormal3fv(normal);
	 glVertex3fv(position);
}

void
Vertex::drawTransp() const
{
	 glVertex3fv(posSkinnee);
}

void
Vertex::drawColor() const
{
	 glEnable(GL_COLOR_MATERIAL);
	 glColorMaterial(GL_FRONT, GL_AMBIENT);
	 glColor3fv(ambient);
	 glColorMaterial(GL_FRONT, GL_DIFFUSE);
	 glColor3fv(diffuse);
	//  glColorMaterial(GL_FRONT, GL_SPECULAR);
//  	 glColor3fv(specular);
	 draw();
	 glDisable(GL_COLOR_MATERIAL);
}

void
Vertex::drawFakeColor() const
{
	 glColor3fv(fakeColor);
	 draw();
}

void
Vertex::drawTex() const
{
	 glTexCoord2f(texcoords[0], texcoords[1]);
	 draw();
}

void
Vertex::drawHard()
{
	 glNormal3f(normal[0], normal[1], normal[2]);
	 glVertex3f(position[0], position[1], position[2]);
}

bool
Vertex::IsSelected()
{
	//  if (selected)
// 			cout << "Vertex selected" << endl;
	 return selected;
}

bool
Vertex::IsInALimb()
{
	 return inalimb;
}

void
Vertex::resetPosition()
{
	 positionCour = position;
}


