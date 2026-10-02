#include <QGLViewer/qglviewer.h>

using namespace std;
using namespace qglviewer;

class Particule{    
private:
    

public:
    void init();
    void draw();
    void animate();
    Vec position;
    Vec vitesseInit;
    Vec vitesseCour;
    float masse;
    bool estVivant;
};
