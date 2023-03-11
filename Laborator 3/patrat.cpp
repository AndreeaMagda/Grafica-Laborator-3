/*

*/
#include "glos.h"

#include "gl.h"
#include "glu.h"
#include "glaux.h"
#include "glut.h"
#include "math.h"

static GLfloat x = 0, y = 0, z = 0, alfa = 0,a=0,b=0,c=0;
static float pi = 3.14159;
int nr_pc = 4;
static GLfloat interval = (2 * pi) / nr_pc;
int raza = 50;
void myInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
}


void CALLBACK MutaStanga()
{
    x = x - 10;
}

void CALLBACK MutaDreapta()
{
    x = x + 10;
}

void CALLBACK MutaSus()
{
    y = y + 10;

}
void CALLBACK MutaJos()
{
    y = y - 10;

}

void CALLBACK rot_z_up(AUX_EVENTREC* event)
{
    alfa = alfa + 10;
}

void CALLBACK rot_z_down(AUX_EVENTREC* event)
{
    alfa = alfa - 10;
}



void CALLBACK display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(x, y, z);
    glRotatef(alfa, 1, 1, 1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  

    glBegin(GL_QUAD_STRIP);
    {


    glColor3f(1.0, 0.0, 1.0); 

        for (int i = 0; i <= nr_pc; i++) {

            a = cos(i * interval) * raza; 
            c = sin(i * interval) * raza;
            b = 4;
            glColor3f(0.6, 0.0, 1.0);
            glVertex3d(a, b, c);
            b = 100;
            glColor3f(0.0, 1.0, 1.0);
            glVertex3d(a, b, c);
            
        }

    }
    glEnd();

    glFlush();
}

#define ISOTROPIC
#ifdef ISOTROPIC
void CALLBACK myReshape(GLsizei w, GLsizei h)
{
    if (!h) {
        return;
    }
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h) {
        glOrtho(-160.0, 160.0, 160.0 * (GLfloat)h / (GLfloat)w, -160.0 * (GLfloat)h / (GLfloat)w, -100.0, 100.0);
    }
    else {
        glOrtho(-160.0 * (GLfloat)w / (GLfloat)h, 160.0 * (GLfloat)w / (GLfloat)h, -160.0, 160.0, -100.0, 100.0);
    }
    glMatrixMode(GL_MODELVIEW);
}
#else
void CALLBACK myReshape(GLsizei w, GLsizei h)
{
    if (!h) return;			//transformare anizotropica, forma se modifica functie de forma(dimens) viewportului
    glViewport(0, 0, w, h);	//daca w>h stabilim ca baza inaltime, si stab unit logica de dimens in fct de h(h/320, 320 lungime lat patrat)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-160.0, 160.0, -160.0, 160.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}
#endif

int main(int argc, char** argv)
{
    auxInitDisplayMode(AUX_SINGLE | AUX_RGB);
    auxInitPosition(0, 0, 800, 600);
    auxInitWindow("Un paralelipiped");
    myInit();
    auxKeyFunc(AUX_LEFT, MutaStanga);
    auxKeyFunc(AUX_RIGHT, MutaDreapta);
    auxKeyFunc(AUX_UP, MutaSus);
    auxKeyFunc(AUX_DOWN, MutaJos);
    auxMouseFunc(AUX_LEFTBUTTON, AUX_MOUSEDOWN, rot_z_up);
    auxMouseFunc(AUX_RIGHTBUTTON, AUX_MOUSEDOWN, rot_z_down);
    
   //auxWireSphere(myReshape);

    auxReshapeFunc(myReshape);
    auxMainLoop(display);
    return(0);
}
