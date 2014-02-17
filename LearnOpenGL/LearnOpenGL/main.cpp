//
//  main.cpp
//  LearnOpenGL
//
//  Created by Chris Jordan on 9/9/13.
//  Copyright (c) 2013 Chris Jordan. All rights reserved.
//

#include <stdlib.h>
#include <cmath>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define KEY_ESCAPE 27

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

void drawCircle(float x, float y, float r, float quality) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(0.0f, 0.0f);

    float numOfTriangles = quality;
    float radiansInCircle = 2 * M_PI;
    float increment = radiansInCircle / numOfTriangles;

    for (float a = 0; a < radiansInCircle + increment; a += increment) {
        glVertex2f(sinf(a) * r, cosf(a) * r);
    }

    glEnd();

    glPopMatrix();
}

void drawDragonScale(float x, float y, float width, float height) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    glBegin(GL_TRIANGLES);

    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, height);
    glVertex2f(width, 0.5f * height);

    glEnd();

    glPopMatrix();
}

void drawScalesInBox(float x, float y, float w, float h, int perRow, int perCol) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    float scaleWidth = w / perRow;
    float scaleHeight = h / perCol;

    for (int row = 0; row < perRow; ++row) {
        if (row % 2 == 0) { // even
            for (int col = 0; col < perCol; ++col) {
                drawDragonScale(row * scaleWidth, col * scaleHeight, scaleWidth, scaleHeight);
            }
        } else { // odd
            for (int col = 0; col < perCol - 1; ++col) {
                drawDragonScale(row * scaleWidth, ((float)col + 0.5f) * scaleHeight, scaleWidth, scaleHeight);
            }
        }
    }

    glPopMatrix();
}

void drawTongue() {
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, 0.15f);
    glVertex2f(0.0f, -0.15f);
    glVertex2f(0.8f, -0.1f);

    glVertex2f(0.0f, 0.15f);
    glVertex2f(0.8f, 0.0f);
    glVertex2f(0.8f, -0.1f);

    glVertex2f(0.8f, 0.0f);
    glVertex2f(0.8f, -0.1f);
    glVertex2f(1.2, 0.15f);

    glVertex2f(1.2f, 0.05f);
    glVertex2f(0.8f, -0.1f);
    glVertex2f(1.2, 0.15f);

    glVertex2f(1.2, 0.15f);
    glVertex2f(1.2f, 0.05f);
    glVertex2f(1.5f, 0.05f);

    glEnd();
}

void drawBasicMouth(float w, float h) {
    float numOfTeeth = 5;
    float teethWidth = (w * 0.6f) / numOfTeeth;
    float teethHeight = 0.3f;

    h -= teethHeight;


    glColor3f(0.9f, 0.0f, 0.0f);


    glBegin(GL_TRIANGLES);

    glVertex2f(0.0f, 0.0f);
    glVertex2f(w, 0.0f);
    glVertex2f(w, -h);

    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, -h);
    glVertex2f(w, -h);

    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, -h);
    glVertex2f(-0.3f, -h - 0.4);

    glEnd();

    glColor3f(0.98f, 0.0f, 0.0f);
    glPushMatrix();
    glRotatef(-90, 0.0f, 0.0f, 1.0f);
    drawScalesInBox(0.0f, -0.2f, h, w + 0.2f, 3, 8);
    glPopMatrix();

    // teeth
    glPushMatrix();
    glTranslatef(0.0f, -h, 0.0f);

    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_TRIANGLES);

    float spacing = 0.09f;

    for (float i = 0; i < numOfTeeth; ++i) {
        float lengthModifier = 1.0f;

        if (i == 0) {
            lengthModifier = 1.8f;
        }

        glVertex2f(w - (i * teethWidth) - 0.1f - i * spacing, 0.0f);
        glVertex2f(w - ((i + 0.5f) * teethWidth) - 0.1f - i * spacing, -teethHeight * lengthModifier);
        glVertex2f(w - ((i + 1.0f) * teethWidth) - 0.1f - i * spacing, 0.0f);
    }
    
    glEnd();

    glPopMatrix();

}

void drawUpperMouth(float w, float h) {
    drawBasicMouth(w, h);

    // snout
    glPushMatrix();
    glTranslatef(w, 0.0f, 0.0f);

    float snoutWidth = 0.4f;
    float snoutHeight = 0.3f;

    glColor3f(0.8f, 0.0f, 0.0f);

    glBegin(GL_TRIANGLES);

    glVertex2f(0.0f, 0.0f);
    glVertex2f(-snoutWidth, 0.0f);
    glVertex2f(-snoutWidth / 2.0f, snoutHeight);

    glEnd();

    glColor3f(0.5f, 0.0f, 0.0f);
    drawCircle(-snoutWidth / 2.0f, 0.1f, 0.09f, 8.0f);

    // tiny hair
    glColor3f(1.0f, 0.4f, 0.0f);
    glBegin(GL_TRIANGLES);

    glVertex2f(0.0f, 0.0f);
    glVertex2f(-0.05f, 0.05f);
    glVertex2f(1.0f, 1.0f);

    glVertex2f(-0.05f, 0.05f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(0.9f, 1.0f);

    glVertex2f(1.0f, 1.0);
    glVertex2f(0.95f, 0.95f);
    glVertex2f(-1.0f, 1.6f);

    glEnd();

    glPopMatrix();
}

void drawDragonHair(float x, float y, float deg, float length, float width) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glRotatef(deg, 0, 0, 1);
    glTranslatef(-width / 2.0f, 0, 0.0f);

    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, width);
    glVertex2f(length, width / 2.0f);
    glEnd();

    glPopMatrix();
}

void drawLowerMouth(float w, float h) {
    drawBasicMouth(w, h);

    // draw beard

    int numOfHair = 5;
    float hairSpacing = w / numOfHair;

    float rangeOfHair = 40.0f;
    float angleBetweenHair = (float)rangeOfHair / (numOfHair - 1);

    for (int i = 0; i < numOfHair; ++i) {
        float green = 0.9f - (i % 2) * 0.4f;
        glColor3f(0.9f + (i % 2) * 0.1f, green, 0.0f);
        drawDragonHair(w - i * hairSpacing, 0.05f, 90 - rangeOfHair / 2.0f + angleBetweenHair * i, 0.4f, 0.3f);
    }
}

void drawDragonHead(float x, float y, float z, float a) {
    float headBaseWidth = 2.0f;
    float headBaseHeight = 2.0f;

    float mouthLength = 1.8f;
    float mouthHeight = headBaseHeight * 0.75f;

    glPushMatrix();
    glTranslatef(x, y - headBaseHeight / 2.0f, z);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);

    glColor3f(0.9f, 0.0f, 0.0f);


    // headBase
    glBegin(GL_TRIANGLES);

    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, headBaseHeight);
    glVertex2f(headBaseWidth * 0.8f, headBaseHeight);

    glVertex2f(0.0f, 0.0f);
    glVertex2f(headBaseWidth * 0.8f, 0.0f);
    glVertex2f(headBaseWidth * 0.8f, headBaseHeight);

    glVertex2f(headBaseWidth, mouthHeight);
    glVertex2f(headBaseWidth * 0.8f, headBaseHeight);
    glVertex2f(headBaseWidth * 0.8f, mouthHeight);

    glEnd();

    // draw scales
    glColor3f(0.98f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(-0.2f * headBaseWidth, headBaseHeight, 0.0f);
    glRotatef(-90, 0.0f, 0.0f, 1.0f);
    drawScalesInBox(0.0f, 0.0f, headBaseWidth, headBaseHeight, 8, 8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(headBaseWidth * 0.8f, headBaseHeight * 0.75f, 0.0f);

    glPushMatrix();
    glRotatef(15.0f, 0.0f, 0.0f, 1.0f);

    drawUpperMouth(mouthLength, mouthHeight / 2.0f);

    glRotatef(-15.0f, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, -mouthHeight, 0.0f);
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(15.0f, 0.0f, 0.0f, 1.0f);

    drawLowerMouth(mouthLength, mouthHeight / 2.0f);

    glPopMatrix();

    // eye
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(0.0f, 0.2f, 0.2f, 10.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(0.1f, 0.25f, 0.1f, 8.0f);

    // tongue
    glTranslatef(0.0f, -mouthHeight / 2.0f, 0.0f);
    drawTongue();

    glPopMatrix();

    // hair
    int numOfHair = 7;
    float hairSpacing = headBaseHeight / numOfHair;

    float rangeOfHair = 60.0f;
    float angleBetweenHair = (float)rangeOfHair / (numOfHair - 1);

    for (int i = 0; i < numOfHair; ++i) {
        float green = 0.9f - (i % 2) * 0.4f;
        glColor3f(0.9f + (i % 2) * 0.1f, green, 0.0f);
        drawDragonHair(-0.3f + fabsf(i - numOfHair / 2.0f) / numOfHair, headBaseHeight - i * hairSpacing + 0.1f, 180 - rangeOfHair / 2.0f + angleBetweenHair * i, 2.0f, 0.4f);
    }

    numOfHair = 4;
    hairSpacing = headBaseWidth * 0.65f / numOfHair;

    for (int i = 0; i < numOfHair; ++i) {
        float green = 0.9f - (i % 2) * 0.4f;
        glColor3f(0.9f + (i % 2) * 0.1f, green, 0.0f);
        drawDragonHair(headBaseWidth * 0.65f - i * hairSpacing, 0.1f, 180 + 50, 0.8f, 0.3f);
    }


    glPopMatrix();
}

void drawDragonClaw(float x, float y, float a, float w, float l) {

    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glRotatef(a * 180 / M_PI, 0.0f, 0.0f, 1.0f);
    glTranslatef(-w / 2.0f, 0.0f, 0.0f);

    glBegin(GL_TRIANGLES);

    glVertex2d(0.0f, 0.0f);
    glVertex2d(w, 0.0f);
    glVertex2d(w / 2.0f, l);

    glEnd();

    glPopMatrix();
}

void drawDragonLeg(float x, float y, float width, float height, float a, float legRot) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glRotatef(a * 180 / M_PI, 0, 0, 1);

    float upperLegHeight = height / 2.0f;
    float lowerLegHeight = height / 3.0f;


    // upper leg
    glColor3f(0.9f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);

    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, upperLegHeight);
    glVertex2f(width, upperLegHeight);

    glVertex2f(0.0f, 0.0f);
    glVertex2f(width, 0.0f);
    glVertex2f(width, upperLegHeight);

    glEnd();

    glColor3f(0.98f, 0.0f, 0.0f);

    glPushMatrix();
    glRotatef(90, 0.0f, 0.0f, 1.0f);
    drawScalesInBox(0.0f, 0.0f, upperLegHeight, -width, 7, 3);
    glPopMatrix();


    // lower leg
    glTranslatef(0.0f, upperLegHeight, 0.0f);
    glRotatef(-legRot, 0, 0, 1);

    glColor3f(0.98f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);

    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, lowerLegHeight);
    glVertex2f(width, lowerLegHeight);

    glVertex2f(0.0f, 0.0f);
    glVertex2f(width, 0.0f);
    glVertex2f(width, lowerLegHeight);

    glEnd();

    glColor3f(0.9f, 0.0f, 0.0f);
    glPushMatrix();
    glRotatef(90, 0.0f, 0.0f, 1.0f);
    drawScalesInBox(0.0f, 0.0f, lowerLegHeight, -width, 5, 3);
    glPopMatrix();

    // hand
    float handLength = 0.7f;
    float handWidth = 1.2f * width;

    glTranslatef((width -handWidth) / 2.0f, lowerLegHeight, 0.0f);


    glColor3f(1.0f, 0.4f, 0.0f);
    glBegin(GL_TRIANGLES);

    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, handLength * 0.75f);
    glVertex2f(handWidth, handLength * 0.75f);

    glVertex2f(0.0f, 0.0f);
    glVertex2f(handWidth, 0.0f);
    glVertex2f(handWidth, handLength * 0.75f);

    glVertex2f(handWidth, handLength * 0.75f);
    glVertex2f(handWidth * 0.75f, handLength);
    glVertex2f(handWidth * 0.5f, handLength * 0.75f);

    glVertex2f(0.0f, handLength * 0.75f);
    glVertex2f(handWidth * 0.25f, handLength);
    glVertex2f(handWidth * 0.5f, handLength * 0.75f);

    glVertex2f(handWidth * 0.5f, handLength * 0.75f);
    glVertex2f(handWidth * 0.25f, handLength);
    glVertex2f(handWidth * 0.75f, handLength);

    glEnd();

    glColor3f(1.0f, 0.2f, 0.0f);
    glPushMatrix();
    glRotatef(90, 0.0f, 0.0f, 1.0f);
    drawScalesInBox(0.0f, 0.0f, handLength, -handWidth, 3, 3);
    glPopMatrix();

    // claws
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0.1f, handLength, 0.0f);

    int numOfClaws = 5;

    float clawWidth = handWidth * 0.9f / numOfClaws;
    float clawLength = 0.5f;

    float rangeOfClaws = M_PI_2;
    float angleBetweenClaws = (float)rangeOfClaws / (numOfClaws - 1);

    for (int i = 0; i < numOfClaws; ++i) {
        drawDragonClaw((i + 0.5f) * clawWidth, -0.1f, rangeOfClaws / 2.0f - angleBetweenClaws * i, clawWidth, clawLength);
    }

    glPopMatrix();
}

void drawDragonSegment(float x, float y, float z, float a, float width, float height) {
    float scaleW = width;
    float scaleH = height;

    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(a * 180 / M_PI, 0, 0, 1);
    glTranslatef(-scaleW / 2.0f, -scaleH / 2.0f, 0.0f);

    glBegin(GL_TRIANGLES);

    glColor3f(0.0f, 0.6f, 1.0f);

    // corners

    // top left
    glColor3f(1.0f, 0.4f, 0.0f);
    glVertex2f(0.0f, 0.75f * scaleH);
    glVertex2f(0.25f * scaleW, 0.75f * scaleH);
    glVertex2f(0.25f * scaleW, scaleH);

    // top right
    glVertex2f(scaleW, 0.75f * scaleH);
    glVertex2f(0.75f * scaleW, 0.75f * scaleH);
    glVertex2f(0.75f * scaleW, scaleH);

    // bot left
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex2f(0.0f, 0.25f * scaleH);
    glVertex2f(0.25f * scaleW, 0.25f * scaleH);
    glVertex2f(0.25f * scaleW, 0.0f);

    // bot right
    glVertex2f(scaleW, 0.25f * scaleH);
    glVertex2f(0.75f * scaleW, 0.25f * scaleH);
    glVertex2f(0.75f * scaleW, 0.0f);


    // filling
    glColor3f(1.0f, 0.0f, 0.0f);

    glVertex2f(0.0f, 0.25f * scaleH);
    glVertex2f(scaleW, 0.25f * scaleH);
    glVertex2f(scaleW, 0.75f * scaleH);

    glVertex2f(0.0f, 0.25f * scaleH);
    glVertex2f(0.0f, 0.75f * scaleH);
    glVertex2f(scaleW, 0.75f * scaleH);

    // bottom edge

    glColor3f(1.0f, 0.7f, 0.0f);
    glVertex2f(0.25f * scaleW, 0.0f);
    glVertex2f(0.25f * scaleW, 0.25f * scaleH);
    glVertex2f(0.75f * scaleW, 0.0f);

    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex2f(0.75f * scaleW, 0.25f * scaleH);
    glVertex2f(0.25f * scaleW, 0.25f * scaleH);
    glVertex2f(0.75f * scaleW, 0.0f);

    // top edge
    glColor3f(1.0f, 0.4f, 0.0f);

    glVertex2f(0.25f * scaleW, 0.75f * scaleH);
    glVertex2f(0.75f * scaleW, 0.75f * scaleH);
    glVertex2f(0.75f * scaleW, scaleH);

    glVertex2f(0.25f * scaleW, 0.75f * scaleH);
    glVertex2f(0.25f * scaleW, scaleH);
    glVertex2f(0.75f * scaleW, scaleH);

    // fin
    float finWidth = 0.4f * scaleW;
    float finHeight = 0.2f * scaleH;

    glColor3f(0.8f, 0.0f, 0.0f);
    glVertex2f(0.5f * scaleW - finWidth / 2.0f, scaleH);
    glVertex2f(0.5f * scaleW + finWidth / 2.0f, scaleH);
    glVertex2f(0.5f * scaleW + finWidth / 2.0f, scaleH + finHeight);

    glEnd();

    // scales
    glTranslatef(0.0f, 0.25f * scaleH, 0.0f);
    glColor3f(1.0f, 0.3f, 0.0f);

    drawScalesInBox(0.0f, 0.0f, scaleW, scaleH / 2.0f, 5, 3);

    glPopMatrix();
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
    glTranslatef(-6.5f, 0, -20.f);

//    drawCoordinates();
//    drawDragonSegment(-2.0f, -2.0f, 0.0f, 0.0f, 2.0f, 2.0f);
//    drawDragonLeg(-5.0f, -2.0f, 0.75f, 3.75, M_PI, 60.0f);

    int numOfScales = 60;
    int taperAmount = 35;
    float anglePerScale = M_PI_4 / 2.0f; // 45
    float fullScaleSize = 2.0f;
    float red = 0.3;
    float redIncrement = 0.03;
    bool readyForLeg = true;

    for (float i = 0.0f, a = 0.0f; i < numOfScales; ++i, red += redIncrement) {

        float scale = fullScaleSize;

        if (numOfScales - i < taperAmount) {
            scale = (numOfScales - i) / taperAmount * fullScaleSize;
        }

        float newA = a + anglePerScale * scale / fullScaleSize;

        if (scale == fullScaleSize && readyForLeg && cos(newA) > cos(a)) { // rising
            drawDragonLeg(a, 2.0f * cos(a), 0.5f * scale, 1.7f * scale, M_PI + M_PI_4, 70.0f);
            drawDragonLeg(a, 2.0f * cos(a), 0.5f * scale, 1.7f * scale, -M_PI / 2.2f + M_PI, 15.0f);
            readyForLeg = false;
        } else if (cos(newA) < cos(a)) { // falling
            readyForLeg = true;
        }

        a = newA;

        drawDragonSegment(a, 2.0f * cos(a), 0.0f, -sin(a), scale, scale);
    }

    drawDragonHead(0.0f, 2.0f, 0, 0);

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

void initRendering() {
    glEnable(GL_MULTISAMPLE);
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f); // dark
//    glClearColor(0.4f, 0.6f, 0.9f, 1.0f); // light
}

int main(int argc, char ** argv){
    // initialize glut
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(800, 600);

    glutCreateWindow("Dragon");
    initRendering();

    glutDisplayFunc(render);
    glutKeyboardFunc(handleKey);
    glutReshapeFunc(handleResize);

    glutMainLoop();
    return 0;
}