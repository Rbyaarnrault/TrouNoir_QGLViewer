/****************************************************************************

 Copyright (C) 2026 Ryan Barrault. All rights reserved.

 This file is part of the QGLViewer library version 2.7.2.

 http://www.libqglviewer.com - contact@libqglviewer.com

 This file may be used under the terms of the GNU General Public License 
 versions 2.0 or 3.0 as published by the Free Software Foundation and
 appearing in the LICENSE file included in the packaging of this file.
 In addition, as a special exception, Ryan Barrault gives you certain 
 additional rights, described in the file GPL_EXCEPTION in this package.

 libQGLViewer uses dual licensing. Commercial/proprietary software must
 purchase a libQGLViewer Commercial License.

 This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

*****************************************************************************/



#include "Viewer.h"
#include <math.h>
#include <stdlib.h> // RAND_MAX
#include <QKeyEvent>
#include <GL/glu.h>

using namespace qglviewer;
using namespace std;

///////////////////////   V i e w e r  ///////////////////////
void Viewer::init() {
    //restoreStateFromFile();
    glDisable(GL_LIGHTING);
    setBackgroundColor(QColor(0,0,0));
    wireframe = true;
    showtriangles = false;
    showvertices = true;
    flatshaded = true;
    
    glPointSize(3.0);
    //setGridIsDrawn();
    setSceneRadius(100);
    help();
    //startAnimation();
          
    ////////////////////////////////TROU NOIR /////////////////////////
    char axe = 'Y';
    Vec posCentreVortex(0,0,70);
    Vec posCentrePuit(0,-40,70);
    float rayonZoneCreation = 80.0f;

    //Particules
    for(int i=0; i<10000; i++){
      particules[i].estVivant = true;

      // Masse aléatoire entre 2kg et 10kg
      // Petit biais pour que j'ai plus de petite particules que de grosses
      float r = ((float)rand() / RAND_MAX);
      particules[i].masse = 0.1f +  (r * r * r)* 4.0f; 

      // Init. vitesses à zéro
      particules[i].vitesseInit = Vec(0.0f, 0.0f, 0.0f);
      particules[i].vitesseCour = particules[i].vitesseInit;

      float angle = ((float)rand() / RAND_MAX)* 2.0f * 3.1415926f;
      
      // Calcul du décalage
        float alea = ((float)rand() / RAND_MAX) * 20.0f;
        float dx = (rayonZoneCreation + alea)  * cos(angle); // Petit décalage aléatoire du cercle de départ
        float dy = (rayonZoneCreation + alea)* sin(angle);
        
        // Placement en fonction de l'axe
        if (axe == 'Z') {
            particules[i].position = Vec(posCentreVortex.x + dx, posCentreVortex.y + dy, posCentreVortex.z);
        } 
        else if (axe == 'Y') {
            particules[i].position = Vec(posCentreVortex.x + dx, posCentreVortex.y, posCentreVortex.z + dy);
        } 
        else if (axe == 'X') {
            particules[i].position = Vec(posCentreVortex.x, posCentreVortex.y + dx, posCentreVortex.z + dy);
        }
    }
}

void drawCircle(float radius, int segments = 50, Vec posCentre = Vec(0,0,0), char axe = 'Z') {
    glBegin(GL_LINE_LOOP);
    
    for(int i = 0; i < segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(segments);
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        
        if (axe == 'Z') {
            //XY
            glVertex3f(posCentre.x + x, posCentre.y + y, posCentre.z);
        }
        else if (axe == 'Y') {
            //XZ
            glVertex3f(posCentre.x + x, posCentre.y, posCentre.z + y);
        }
        else if (axe == 'X') {
            //YZ
            glVertex3f(posCentre.x, posCentre.y + x, posCentre.z + y);
        }
    }
    glEnd();
}

void Viewer::draw() {

    /////////////////////////////////////// TROU NOIR //////////////////////////////////////////////////
    // Trou noir = combinaison de vortex + puit ?
    // Zone de mort et pas juste un point

    // DEBUG
    // Spère de mon Puit
    // glColor3f(1.0f, 0.0f, 0.0f); //rouge
    // glPushMatrix();
    // glTranslatef(0,-10,70);
    // static GLUquadric* quad = gluNewQuadric();
    // gluQuadricDrawStyle(quad, GLU_LINE);
    // gluSphere(quad, 10.0, 20, 20);
    // glPopMatrix();

    // // Spère de mon vortex
    // glColor3f(0.0f, 1.0f, 0.0f); //vert
    // glPushMatrix();
    // glTranslatef(0,0,70);
    // static GLUquadric* quad2 = gluNewQuadric();
    // gluQuadricDrawStyle(quad2, GLU_LINE);
    // gluSphere(quad2, 10.0, 20, 20);
    // glPopMatrix();

    // Particules
    //glColor3f(0.3f, 0.3f, 1.0f); //bleu

    char axe = 'Y'; 
    Vec posCentreVortex(0, 0, 70); 
    Vec posCentrePuit(0,-40,70);

    for(int i = 0; i < 10000; i++) {

        float rCol = (float)rand() / RAND_MAX;
        float intensRouge = 0.3f + (rCol * rCol * rCol) * 0.6f; 
        glColor3f(intensRouge, 0.3f, 1.0f);

        glPointSize(particules[i].masse); //En fonction de la masse
        glBegin(GL_POINTS);

        if(particules[i].estVivant){
          glVertex3f(particules[i].position.x, particules[i].position.y, particules[i].position.z);
        }
        glEnd();

        // if (i<10){
        //     // Debug Forces
        //     glColor3f(1.0,0.0,0.0);
        //     glBegin(GL_LINES);
        //     glVertex3fv(particules[i].position); // Puit
        //     glVertex3fv(posCentrePuit);

        //     glColor3f(0,1,0);
        //     glVertex3fv(particules[i].position); // Vortex
        //     glVertex3fv(posCentreVortex);

        //     glEnd(); }
    }
}

void Viewer::animate() {
    Vec posCentreVortex(0, 0, 70);
    Vec posCentrePuit(0, -10, 70);
    float rayonMortCarre = 10.0f * 10.0f; 

    float intensPuit = 200.0f; 
    float intensVortex = 300.0f; // Le vortex doit être plus fort pour faire de belles boucles
    float dt = 0.014f;

    for(int i = 0; i < 10000; i++) {
        if (particules[i].estVivant) {
            Vec directionPuit = posCentrePuit - particules[i].position;
            Vec directionVortex = posCentreVortex - particules[i].position;
            
            // Normalisation
            directionPuit.normalize();
            directionVortex.normalize();

            // Forces
            Vec forcePuit = directionPuit * intensPuit;
            Vec axeY(0.0f, 1.0f, 0.0f);
            Vec forceVortex = (axeY ^ directionVortex) * intensVortex;
            Vec sommeForce = forcePuit + forceVortex;

            // Zone de mort ? Si oui je réinitialise la particule
            Vec distPuit = posCentrePuit - particules[i].position;
            if (distPuit.squaredNorm() < rayonMortCarre) {
                
                float r = (float)rand() / RAND_MAX;
                particules[i].masse = 0.1f + (r * r * r) * 4.0f; 
                particules[i].vitesseCour = Vec(0.0f, 0.0f, 0.0f);

                float rayonZoneCreation = 80.0f;
                float angle = ((float)rand() / RAND_MAX) * 2.0f * 3.1415926f;
                float alea = ((float)rand() / RAND_MAX) * 20.0f;
                float dx = (rayonZoneCreation + alea)  * cos(angle); // Petit décalage aléatoire du cercle de départ
                float dy = (rayonZoneCreation + alea)* sin(angle);
                particules[i].position = Vec(posCentreVortex.x + dx, posCentreVortex.y, posCentreVortex.z + dy);
                
                continue; 
            }

            Vec acc = sommeForce / particules[i].masse; 
            particules[i].vitesseCour += acc * dt;

            // Frottements
            particules[i].vitesseCour *= 0.94f;

            float vitesseMax = 80.0f; // Maximum pour pas avoiir de pb
            if (particules[i].vitesseCour.norm() > vitesseMax) {
                particules[i].vitesseCour.normalize();
                particules[i].vitesseCour *= vitesseMax;
            }

            // Mise à jour de la position
            particules[i].position += particules[i].vitesseCour * dt;
        }
    }
   
    computeNormals();
}


void Viewer::computeNormals()
{
    //cout << "faces.size = " << faces.size() << endl;
    faces_normals.clear();
    //Iteration sur tous les points pour mettre les normales a 0
    for (vector<Vertex*>::iterator vit = vertices.begin();
         vit != vertices.end(); vit++)
      { (*vit)->normal = Vec(0,0,0);}
    
    for (std::vector<int>::iterator fit = faces.begin();
               fit != faces.end(); ++fit)
    {
        Vertex * p1 = vertices[(* fit)];
        fit++;
        Vertex * p2 = vertices[(* fit)];
        fit++;
        Vertex * p3 = vertices[(* fit)];
        Vec n = (p2->position - p1->position) ^ (p3->position - p1->position);
        p1->normal += n;
        p2->normal += n;
        p3->normal += n;
        n.normalize();
        faces_normals.push_back(n);
    }
    //Normalisation des normales par point
    
    for (vector<Vertex*>::iterator vit = vertices.begin();
         vit != vertices.end(); vit++)
    { (*vit)->normal.normalize();}
    
}

void Viewer::keyPressEvent(QKeyEvent *e)
{
  const Qt::KeyboardModifiers modifiers = e->modifiers();
  bool handled = true; // Permet de savoir si on a intercepté la touche

  if ((e->key() == Qt::Key_W) && (modifiers == Qt::NoButton)) {
    wireframe = !wireframe;
  }
  else if ((e->key() == Qt::Key_T) && (modifiers == Qt::NoButton)) {
    showtriangles = !showtriangles;
  }
  else if ((e->key() == Qt::Key_V) && (modifiers == Qt::NoButton)) {
    showvertices = !showvertices;
  }
  else if ((e->key() == Qt::Key_F) && (modifiers == Qt::NoButton)) {
    flatshaded = !flatshaded;
  }
  else if ((e->key() == Qt::Key_G) && (modifiers == Qt::NoButton)) {
    // Inverse l'état actuel de la grille
    setGridIsDrawn(!gridIsDrawn()); 
  }
  else if ((e->key() == Qt::Key_A) && (modifiers == Qt::NoButton)) {
    // Inverse l'état actuel des axes
    setAxisIsDrawn(!axisIsDrawn()); 
  }

  else {
    // Si la touche n'est pas gérée, raccourci clavier par défaut de QGLViewer
    handled = false; 
  }

  if (handled) {
    // Si on a modifié quelque chose, on met à jour l'affichage
    update();
  } else {
    // Sinon, on laisse QGLViewer gérer ses raccourcis par défaut (Entrée, Échap, etc.)
    QGLViewer::keyPressEvent(e);
  }
}

QString Viewer::helpString() const {
  QString text("<h2>Trou Noir(Dark Hole) A n i m a t i o n</h2>");
  text += "Use the <i>animate()</i> function to implement the animation part "
          "of your ";
  text += "application. Once the animation is started, <i>animate()</i> and "
          "<i>draw()</i> ";
  text += "Press <b>Return</b> to start/stop the animation.";
  return text;
}

