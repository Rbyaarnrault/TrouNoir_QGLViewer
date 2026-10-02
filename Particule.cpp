#include <math.h>
#include <stdlib.h>
#include "Particule.h"
#include <QGLViewer/qglviewer.h>

using namespace std;

void Particule::init(){
    position = Vec(0,0,0);
    vitesseInit = Vec(0,0,0);
    vitesseCour = Vec(0,0,0);
    masse = 0;
    estVivant = true;
}

void Particule::draw(){
    glBegin(GL_POINTS);
    glVertex3fv(position);
    glEnd();

}

void Particule::animate(){

}

