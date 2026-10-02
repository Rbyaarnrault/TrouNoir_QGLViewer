#ifndef VertexHEADER
#define VertexHEADER

#if defined(WIN32)
#  pragma warning (disable : 4786) // disable warn truncated name with STL
#endif

#include <set>


#include <QGLViewer/qglviewer.h>


using namespace std;
using namespace qglviewer;


class Vertex
{
	 public:
			Vertex();
//			Vertex(const POINT& p);
			Vertex(const Vec& p);
			void draw() const;
			void drawColor() const;
			void drawFakeColor() const;
			void drawTex() const;
			void drawTransp() const;
			void drawHard();
			bool IsSelected();
			bool IsInALimb();
			void resetPosition();

						
			qglviewer::Vec position;
			qglviewer::Vec posSpecial;
			qglviewer::Vec posSkinnee;
			qglviewer::Vec positionCour;
			qglviewer::Vec normalsurf;
			qglviewer::Vec normal;
			qglviewer::Vec ambient;
			qglviewer::Vec diffuse;
			qglviewer::Vec specular;
			qglviewer::Vec fakeColor;
			qglviewer::Vec texcoords;
			bool selected;
			bool inalimb; /* Peut ptet mettre un entier pour savoir quel
										 * limb */
			bool isspecial;						
	 private:
			int lnum;		
};

#endif
