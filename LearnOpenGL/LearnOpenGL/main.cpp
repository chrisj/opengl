#include <stdlib.h>
#include <cmath>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define KEY_ESCAPE 27

void initRendering() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
}

void drawCoordinates() {
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -100.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);

    glEnd();
}

void drawMouth(float w, float h) {

    float numOfTeeth = 5;
    float teethWidth = w / numOfTeeth;
    float teethHeight = 0.4f;

    h -= teethHeight;


    glColor3f(0.7f, 0.4f, 1.0f);


    glBegin(GL_TRIANGLES);

    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(w, 0.0f, 0.0f);
    glVertex3f(w, -h, 0.0f);

    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, -h, 0.0f);
    glVertex3f(w, -h, 0.0f);

    glEnd();

    glPushMatrix();
    glTranslatef(0.0f, -h, 0.0f);

    glColor3f(0.0f, 0.7f, 0.7f);

    glBegin(GL_TRIANGLES);

    for (float i = 0; i < numOfTeeth; ++i) {
        glVertex3f(i * teethWidth, 0.0f, 0.0f);
        glVertex3f((i + 0.5f) * teethWidth, -teethHeight, 0.0f);
        glVertex3f((i + 1.0f) * teethWidth, 0.0f, 0.0f);
    }

    glEnd();

    glPopMatrix();
}

void drawDragonHead(float x, float y, float z, float a) {
    float headBaseWidth = 2.0f;
    float headBaseHeight = 2.0f;

    glPushMatrix();
    glTranslatef(x, y - headBaseHeight / 2.0f, z);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);

//    glRotatef(a * 180 / M_PI, 0, 0, 1);

    glColor3f(1.0f, 0.0f, 0.0f);


    glBegin(GL_QUADS);

    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, headBaseWidth, 0.0f);
    glVertex3f(headBaseHeight, headBaseWidth, 0.0f);
    glVertex3f(headBaseHeight, 0.0f, 0.0f);

    glEnd();

    float mouthLength = 1.8f;
    float mouthHeight = headBaseHeight / 2.0f;

    glTranslatef(headBaseWidth, headBaseHeight, 0.0f);

    glPushMatrix();
    glRotatef(15.0f, 0.0f, 0.0f, 1.0f);

    drawMouth(mouthLength, mouthHeight);

    glRotatef(-15.0f, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, -headBaseHeight, 0.0f);
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(15.0f, 0.0f, 0.0f, 1.0f);

    drawMouth(mouthLength, mouthHeight);

    glPopMatrix();



    // horn
    glColor3f(0.9f, 0.9f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-0.8f, 0.0f, 0.0f);
    glVertex3f(-2.5f, 0.8f, 0.0f);
    glEnd();


    glPopMatrix();
}

void drawDragonScale(float x, float y, float z, float a) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(a * 180 / M_PI + 90, 0, 0, 1);

    glColor3f(1.0f, 0.6f, 0.0f);

    glBegin(GL_TRIANGLES);

    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0);
    glVertex3f(1.0f, -1.0f, 0);

    glEnd();
    glPopMatrix();
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
    glTranslatef(0.0f, 0, -20.f);

    drawCoordinates();

    drawDragonHead(0.0f, 2.5f, 0, 0);

    for (float a = 0; a < M_PI * 4.0f; a += M_PI / 6.0f) {
        drawDragonScale(1.5f * a, 2.5f*cos(a), 0, -sin(a));
    }

    glPopMatrix();

    glutSwapBuffers();
}

void handleKey(unsigned char key, int x, int y){
    switch (key) {
        case KEY_ESCAPE:
            exit(0);
            break;
        default:
            break;
    }
}

void handleResize(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 1.0, 200);
}

int main(int argc, char ** argv){
    // initialize glut
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(400, 400);

    glutCreateWindow("HW2");
    initRendering();

    glutDisplayFunc(render);
    glutKeyboardFunc(handleKey);
    glutReshapeFunc(handleResize);

    glutMainLoop();
    return 0;
}