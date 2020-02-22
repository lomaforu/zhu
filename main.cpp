#include "glcamera.h"

#include <iostream>
#include <GL/glut.h>
#include <GL/glu.h>
#include <cmath>

using namespace std;

GLfloat xRot = 80.0f;
GLfloat yRot = 0.0f;

GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;

GLfloat windowWidth = 100;
GLfloat windowHeight = 100;

#define GL_PI 3.1415f

GLfloat  whiteLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat  sourceLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat	 lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };

GLCamera camera;

void TimerFunction(int value)
{
    //glutPostRedisplay();
    //glutTimerFunc(100,TimerFunction,1);
}

void SetupRC(void)
{
    // Light values and coordinates
    glEnable(GL_DEPTH_TEST);	// Hidden surface removal
    glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
    glEnable(GL_CULL_FACE);		// Do not calculate inside of jet

    // Enable lighting
    glEnable(GL_LIGHTING);

    // Setup and enable light 0
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
    glEnable(GL_LIGHT0);

    // Enable color tracking
    glEnable(GL_COLOR_MATERIAL);

    // Set Material properties to follow glColor values
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // Black blue background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

    camera.set_perspective(800,600);
    camera.update(0.0f,0.0f,10.0f
                  ,0.0f,0.0f,0.0f);
}

void RenderScene(void)
{
    static GLfloat fMoonRot = 0.0f;
    static GLfloat fEarRot = 0.0f;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();

    camera.look_at();

    glTranslatef(0.0f,0.0f,-300.0f);
    //sun
    glColor3ub(255,255,0);
    glDisable(GL_LIGHTING);
    glutSolidSphere(15.0f,15,15);
    glEnable(GL_LIGHTING);

    GLfloat lightPos[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);

    glRotatef(fEarRot,0.0f,1.0f,0.0f);
    //earth
    glColor3ub(0,0,255);
    glTranslatef(105.0f,0.0f,0.0f);
    glutSolidSphere(15.0f,15,15);

    //moon
    glColor3ub(200,200,200);
    glRotatef(fMoonRot,0.0f,1.0f,0.0f);
    glTranslatef(30.0f,0.0f,0.0f);
    //fMoonRot += 15.0f;
    if (fMoonRot > 360.0f)
        fMoonRot = 0.0f;

    glutSolidSphere(6.0f,15,15);
    glPopMatrix();

    //fEarRot += 5.0f;
    if (fEarRot > 360.0f)
        fEarRot = 0.0f;

    glutSwapBuffers();
}

void SpecialKey(GLint key,GLint x,GLint y)
{
    if (key == GLUT_KEY_UP)
    {
        //camera.move_forward(1);
        camera.turn_up(0.01f);
    }
    else if (key == GLUT_KEY_DOWN)
    {
        //camera.move_backward(1);
        camera.turn_down(0.01f);
    }
    else if (key == GLUT_KEY_RIGHT)
    {
        camera.move_right(1);
        //camera.turn_right(0.01f);
    }
    else if (key == GLUT_KEY_LEFT)
    {
        camera.move_left(1);
        //camera.turn_left(0.01f);
    }

    glutPostRedisplay();
}

void ChangeSize(GLsizei w,GLsizei h)
{
    GLfloat fAspect;

    if (h == 0)
        h = 1;

    glViewport(0,0,w,h);
    fAspect = (GLfloat)w/(GLfloat)h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f,fAspect,1.0,425.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc,char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_STENCIL);
    glutInitWindowSize(800,600);
    glutCreateWindow("Simple");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKey);
    glutTimerFunc(100,TimerFunction,1);

    SetupRC();

    glutMainLoop();

    return 0;
}
