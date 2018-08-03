//  ========================================================================
//  COSC363: Computer Graphics (2018);  University of Canterbury.
//
//  FILE NAME: Yard.cpp
//  See Lab03.pdf for details.
//  ========================================================================

#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include "loadTGA.h"
#include <GL/freeglut.h>
#include <math.h>
using namespace std;

float theta = 20;
int direction = -1;
int count = 0;
const int N = 50;
GLUquadric *sphere = gluNewQuadric();

float skux = 10*M_PI/180;

float vx[N] = {0, 8, 7, 6, 5, 4, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
              2, 2, 2, 3, 4, 5, 6, 7, 8, 9, 9.1, 9.2, 9.3, 9.4, 9.5, 9.6, 9.7, 9.8, 9.9, 10,
              10.1, 10.2, 10.3, 10.4, 10.5, 10.6, 10.7, 10.8, 10.9, 1};
float vy[N] = {0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18,
               19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
               39, 40, 41, 42, 43, 43, 42, 41, 40, 39};
float vz[N] = {0};


#define GL_CLAMP_TO_EDGE 0x812F   //To get rid of seams between textures
GLuint txId[10];   //Texture ids
float angle=-90*M_PI/180, look_x, look_y, look_z, eye_x = 60, eye_y = 5, eye_z = 0, camf1 = 0, eyex1, eyez1, angle1;  //Camera parameters
//--------------------------------------------------------------------------------
void loadTexture()
{
    glGenTextures(10, txId);     // Create 3 texture ids

    glBindTexture(GL_TEXTURE_2D, txId[0]);  //Use this texture
    loadTGA("BrickWall.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, txId[1]);  //Use this texture
    loadTGA("GrassFloor.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, txId[8]);  //Use this texture for roof
    loadTGA("Roof.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, txId[9]);
    loadTGA("Metal.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    ////////////////////////////////////SKYBOX//////////////////////////////////////////////////
     // *** left ***
    glBindTexture(GL_TEXTURE_2D, txId[2]);
    loadTGA("mp_fcih/fat-chance-in-hell_ft.tga"); //
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // *** front ***
    glBindTexture(GL_TEXTURE_2D, txId[3]);
    loadTGA("mp_fcih/fat-chance-in-hell_lf.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // *** right ***
    glBindTexture(GL_TEXTURE_2D, txId[5]);
    loadTGA("mp_fcih/right.tga"); //this one screws out
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // *** back***
    glBindTexture(GL_TEXTURE_2D, txId[4]);
    loadTGA("mp_fcih/fat-chance-in-hell_bk.tga");
    //loadTGA("mp_fcih/fat-chance-in-hell_rt.tga"); // rt
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // *** top ***
    glBindTexture(GL_TEXTURE_2D, txId[6]);
    loadTGA("mp_fcih/fat-chance-in-hell_up.tga"); //up
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // *** down ***
    glBindTexture(GL_TEXTURE_2D, txId[7]);
    loadTGA("mp_fcih/fat-chance-in-hell_dn.tga"); //dn
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
}

//--------------------------------------------------------------------------------
void special(int key, int x, int y)
{
    if(key == GLUT_KEY_LEFT && camf1 == 0) angle -= 0.1;  //Change direction
    else if(key == GLUT_KEY_RIGHT && camf1 == 0) angle += 0.1;
    else if(key == GLUT_KEY_F1)
    {
        if(camf1 == 0){
            eyex1 = eye_x;
            eyez1 = eye_z;
            angle1 = angle;
            eye_x = 8;
            eye_z = 8;
            angle = 36.8;
            eye_y = 5 + (theta * 0.05);
            camf1 = 1;
        } else {
            eye_x = eyex1;
            eye_z = eyez1;
            angle = angle1;
            camf1 = 0;

        }

    }
    else if(key == GLUT_KEY_DOWN && camf1 == 0)
    {  //Move backward
        eye_x -= 0.5*sin(angle);
        eye_z += 0.5*cos(angle);
    }
    else if(key == GLUT_KEY_UP && camf1 == 0)
    { //Move forward
        eye_x += 0.5*sin(angle);
        eye_z -= 0.5*cos(angle);
    }
    look_x = eye_x + 100*sin(angle);
    look_z = eye_z - 100*cos(angle);
    glutPostRedisplay();
}

//--------------------------------------------------------------------------------

void initialise()
{
    glEnable(GL_COLOR_MATERIAL);
    loadTexture();
    glEnable(GL_TEXTURE_2D);
    glClearColor(0., 1., 1., 1.);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    float grey[4] = {0.2, 0.2, 0.2, 1.0};
    float white[4]  = {1.0, 1.0, 1.0, 1.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, grey);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    glLightfv(GL_LIGHT1, GL_AMBIENT, grey);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT1, GL_SPECULAR, white);

    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 50);

    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_NORMALIZE);
    glClearColor (0.0, 0.0, 0.0, 0.0);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
}

//--------------------------------------------------------------------------------

void walls()
{
    glBindTexture(GL_TEXTURE_2D, txId[0]);

    glBegin(GL_QUADS);

    ////////////////////// WALL ///////////////////////
    glTexCoord2f(0.0, 2.0);
    glVertex3f(-15, 10, -15);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(-15, -1, -15);

    glTexCoord2f(12.0, 0.0);
    glVertex3f(15, -1, -15);

    glTexCoord2f(12.0, 2.0);
    glVertex3f(15, 10, -15);

    ////////////////////// WALL ///////////////////////
    glTexCoord2f(0.0, 2.0);
    glVertex3f(-15, 10, 15);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(-15, -1, 15);

    glTexCoord2f(12.0, 0.0);
    glVertex3f(15, -1, 15);

    glTexCoord2f(12.0, 2.0);
    glVertex3f(15, 10, 15);

    ////////////////////// WALL ///////////////////////
    glTexCoord2f(0.0, 2.0);
    glVertex3f(-15, 10, -15);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(-15, -1, -15);

    glTexCoord2f(12.0, 0.0);
    glVertex3f(-15, -1, 15);

    glTexCoord2f(12.0, 2.0);
    glVertex3f(-15, 10, 15);


    ////////////////////// FRONT LEFT WALL ///////////////////////
    glTexCoord2f(0.0, 2.0);
    glVertex3f(15, 10, 3);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(15, -1, 3);

    glTexCoord2f(12.0, 0.0);
    glVertex3f(15, -1, 15);

    glTexCoord2f(12.0, 2.0);
    glVertex3f(15, 10, 15);

    ////////////////////// FRONT RIGHT WALL ///////////////////////
    glTexCoord2f(0.0, 2.0);
    glVertex3f(15, 10, -15);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(15, -1, -15);

    glTexCoord2f(12.0, 0.0);
    glVertex3f(15, -1, -3);

    glTexCoord2f(12.0, 2.0);
    glVertex3f(15, 10, -3);

    ////////////////////// FRONT TOP ///////////////////////
    glTexCoord2f(0.0, 1.0);
    glVertex3f(15, 10, -3);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(15, 7, -3);

    glTexCoord2f(3.0, 0.0);
    glVertex3f(15, 7, 3);

    glTexCoord2f(3.0, 1.0);
    glVertex3f(15, 10, 3);

    //glTexCoord2f(2.0, 1.0);
    //glVertex3f(15, 10, -3);

    //glTexCoord2f(2.0, 2.0);
    //glVertex3f(15, 7, -3);

    //glTexCoord2f(1.0, 2.0);
    //glVertex3f(15, 7, 3);

    //glTexCoord2f(1.0, 1.0);
    //glVertex3f(15, 10, 3);

    glEnd();
}
//========================================================================================

void skybox(){
    glEnable(GL_TEXTURE_2D);

  ////////////////////// LEFT WALL ///////////////////////
  glBindTexture(GL_TEXTURE_2D, txId[2]);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 0.0); glVertex3f(-1000,  -500, 1000);

  glTexCoord2f(1.0, 0.0); glVertex3f(-1000, -500, -1000);

  glTexCoord2f(1.0, 1.0); glVertex3f(-1000, 500., -1000);

  glTexCoord2f(0.0, 1.0); glVertex3f(-1000, 500, 1000);
  glEnd();

  ////////////////////// FRONT WALL ///////////////////////
  glBindTexture(GL_TEXTURE_2D, txId[3]);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 0.0);
  glVertex3f(-1000, -500, -1000);
  glTexCoord2f(1.0, 0.0);
  glVertex3f(1000, -500., -1000);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(1000, 500, -1000);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(-1000,  500, -1000);
  glEnd();

 ////////////////////// RIGHT WALL ///////////////////////
  glBindTexture(GL_TEXTURE_2D, txId[4]);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 0.0);
  glVertex3f(1000,  -500, -1000);
  glTexCoord2f(1.0, 0.0);
  glVertex3f(1000, -500, 1000);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(1000, 500,  1000);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(1000,  500,  -1000);
  glEnd();

  ////////////////////// REAR WALL ////////////////////////
  glBindTexture(GL_TEXTURE_2D, txId[5]);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 0.0);
  glVertex3f( 1000, -500, 1000);
  glTexCoord2f(1.0, 0.0);
  glVertex3f(-1000, -500,  1000);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(-1000, 500,  1000);
  glTexCoord2f(0.0, 1.0);
  glVertex3f( 1000, 500, 1000);
  glEnd();

  /////////////////////// TOP //////////////////////////
  glBindTexture(GL_TEXTURE_2D, txId[6]);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 0.0);
  glVertex3f(-1000, 500, -1000);
  glTexCoord2f(1.0, 0.0);
  glVertex3f(1000, 500,  -1000);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(1000, 500,  1000);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(-1000, 500, 1000);
  glEnd();

  /////////////////////// FLOOR //////////////////////////
  glBindTexture(GL_TEXTURE_2D, txId[7]);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 0.0);
  glVertex3f(-1000, -500, 1000);
  glTexCoord2f(1.0, 0.0);
  glVertex3f(1000, -500,  1000);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(1000, -500, -1000);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(-1000, -500, -1000);
  glEnd();

}

//---------------------------------------------------------------------

void floor()
{
    glBindTexture(GL_TEXTURE_2D, txId[1]);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 1000.0);
         glVertex3f(-1000, 1, -1000);

         glTexCoord2f(0.0, 0.0);
         glVertex3f(-1000, 1, 1000);

         glTexCoord2f(1000.0, 0.0);
         glVertex3f(1000, 1, 1000);

         glTexCoord2f(1000.0, 1000.0);
         glVertex3f(1000, 1, -1000);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, txId[9]);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 16.0);
         glVertex3f(-15, 1.1, -15);

         glTexCoord2f(0.0, 0.0);
         glVertex3f(-15, 1.1, 15);

         glTexCoord2f(16.0, 0.0);
         glVertex3f(15, 1.1, 15);

         glTexCoord2f(16.0, 16.0);
         glVertex3f(15, 1.1, -15);
    glEnd();
}


//--------------------------------------------------------------------------------
void floor1()
{
    float white[4] = {1., 1., 1., 1.};
    float black[4] = {0};
    glColor4f(0.7, 0.7, 0.7, 1.0);
    glNormal3f(0.0, 1.0, 0.0);

    glMaterialfv(GL_FRONT, GL_SPECULAR, black);
    glPushMatrix();
    glTranslatef(-1,0, -1.25);
    glScalef(0.15, 0.15, 0.15);
    glBegin(GL_QUADS);
    for(int i = -100; i < 100; i++)
    {
        for(int j = -100;  j < 100; j++)
        {
            glVertex3f(i, 0, j);
            glVertex3f(i, 0, j+1);
            glVertex3f(i+1, 0, j+1);
            glVertex3f(i+1, 0, j);
        }
    }
    glEnd();
    glPopMatrix();
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);

}
//--------------------------------------------------------------------------------

void roof()
{
    glBindTexture(GL_TEXTURE_2D, txId[8]);  //replace with a texture

    glBegin(GL_QUADS);
    ////////////////// ROOF 1 //////////////////////
    glTexCoord2f(0.0, 2.0);
    glVertex3f(-15, 10, -15);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(-0, 16, -0);

    glTexCoord2f(12.0, 0.0);
    glVertex3f(-0, 16, -0);

    glTexCoord2f(12.0, 2.0);
    glVertex3f(15, 10, -15);

    ////////////////////// ROOF BACK ///////////////////////
    glTexCoord2f(0.0, 2.0);
    glVertex3f(-0, 16, -0);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(-15, 10, -15);

    glTexCoord2f(12.0, 0.0);
    glVertex3f(-15, 10, 15);

    glTexCoord2f(12.0, 2.0);
    glVertex3f(-0, 16, 0);

    ////////////////////// WALL ///////////////////////
    glTexCoord2f(0.0, 2.0);
    glVertex3f(-0, 16, 0);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(-15, 10, 15);

    glTexCoord2f(12.0, 0.0);
    glVertex3f(15, 10, 15);

    glTexCoord2f(12.0, 2.0);
    glVertex3f(0, 16, 0);

    ////////////////////// FRONT LEFT WALL ///////////////////////
    glTexCoord2f(0.0, 2.0);
    glVertex3f(0, 16, -0);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(15, 10, -15);

    glTexCoord2f(12.0, 0.0);
    glVertex3f(15, 10, 15);

    glTexCoord2f(12.0, 2.0);
    glVertex3f(0, 16, 0);

    glEnd();
}

//-----------------------------------------------
typedef struct
{
    float zj;
    float ydire;
    float zdire;
    float xdire;
    float xj;
    float yj;
}Particles;


Particles particle[100];

void update_position(){
    for (int j=0;j<100;j++)
    {
        particle[j].xdire = (rand()%50)-25.0,
        particle[j].ydire=(rand()%80)-25.0+ 1,
        particle[j].zdire=(rand()%50)-25.0;
    }
    glColor3f(0.5, 0.5, 0.5);
    for (int j = 0;j < 100; j++)
    {
        glTranslatef(particle[j].xj,particle[j].yj,particle[j].zj);
        glutSolidCube(0.1);
        glTranslatef(-particle[j].xj,-particle[j].yj,-particle[j].zj);
        particle[j].xj += particle[j].xdire/3000;
        particle[j].yj += particle[j].ydire/3000;
        particle[j].zj += particle[j].zdire/3000;
        if (particle[j].yj>=1)
        {
            particle[j].xj=-0.08;
            particle[j].yj=0.0;
            particle[j].zj=-0.08;
        }
    }
}
//--------------------------------------------------------------------------------

void drawAlienl()
{
    float lgt_pos1[] = { (float)(-0), 0 ,(float)( -0) ,1.0}; //
    float spotdir[]={0 , -10.0, 0};

    glPushMatrix();
    glScalef(0.3, 0.3, 0.3);
    glTranslatef(-12 + theta * 1.8,20,-9 + theta * 0.9);
    glLightfv(GL_LIGHT1, GL_POSITION, lgt_pos1);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotdir);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 10.0);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT,0.01);
    glRotatef(theta * 1.8, 0, 1, 0);

    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glColor3f(0.5, 0.5, 0.5);
    glPushMatrix();
      glTranslatef(0, 5.5, 0);
      glScalef(13, 3, 13);
      glutSolidSphere(0.7, 22, 22);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glColor3f(0.59, 0.96, 0.05);
    glPushMatrix();
      glTranslatef(0, 20.5, 0);
      glScalef(8, 8, 8);
      glutSolidSphere(0.7, 22, 22);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
      glTranslatef(5.5, 22.5, 0);
      glScalef(1, 1, 1);
      glutSolidSphere(0.7, 22, 22);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
      glTranslatef(4.5, 22.5, 3);
      glScalef(1, 1, 1);
      glutSolidSphere(0.7, 22, 22);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glColor3f(0.59, 0.96, 0.05);
    glPushMatrix();
      glTranslatef(0, 13.5, 0);
      glScalef(9, 9, 9);
      glutSolidSphere(0.7, 22, 22);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glColor3f(0.59, 0.96, 0.05);
    glPushMatrix();
      glTranslatef(0, 20.5, 0);
      glScalef(1, 16, 1);
      glutSolidSphere(0.7, 22, 22);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glColor3f(0.59, 0.96, theta);
    glPushMatrix();
      glTranslatef(0, 30.5, 0);
      glScalef(2, 2, 2);
      glutSolidSphere(0.7, 22, 22);
    glPopMatrix();

   glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
      glTranslatef(5, 20.5, 1);
      glScalef(1.5, 1.5, 2.5);
      glutSolidSphere(0.7, 22, 22);
    glPopMatrix();



    glPopMatrix();
    glPopMatrix();
}

//--------------------------------------------------------------------------------
void drawDog()
{
    glPushMatrix();
    glScalef(0.4, 0.4, 0.4);
    glTranslatef(25, 4, -28);
    glRotatef(-35, 0, 1,0);

    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glColor3f(0.45, 0.31, 0.09);
    glPushMatrix();
      glTranslatef(0, 5.5, 0);
      glScalef(7, 5, 15);
      glutSolidSphere(0.7, 22, 22);
    glPopMatrix();

    glColor3f(0.45, 0.31, 0.09);
    glPushMatrix();
      glTranslatef(-0.8, 4, 3);
      glRotatef(-theta, 1, 0, 0);
      glTranslatef(0.8, -4, 0);
      glTranslatef(-3.6, 2.2, 2);
      glScalef(3, 6.4, 3);
      glutSolidSphere(0.7, 22, 22);
    glPopMatrix();

    glColor3f(0.45, 0.31, 0.09);
    glPushMatrix();
      glTranslatef(0.8, 4, 3);
      glRotatef(theta, 1, 0, 0);
      glTranslatef(-0.8, -4, 0);
      glTranslatef(3.6, 2.2, 2);
      glScalef(3, 6.4, 3);
      glutSolidSphere(0.7, 22, 22);
    glPopMatrix();

    glColor3f(0.45, 0.31, 0.09);
    glPushMatrix();
      glTranslatef(0.8, 4, 3);
      glRotatef(-theta * 0.5, 1, 0, 0);
      glTranslatef(-0.8, -4, 0);
      glTranslatef(3.6, 2.2, -6);
      glScalef(3, 6.4, 3);
      glutSolidSphere(0.7, 22, 22);
    glPopMatrix();

    glColor3f(0.45, 0.31, 0.09);
    glPushMatrix();
      glTranslatef(-0.8, 4, 3);
      glRotatef(theta * 0.5, 1, 0, 0);
      glTranslatef(0.8, -4, 0);
      glTranslatef(-3.6, 2.2, -6);
      glScalef(3, 6.4, 3);
      glutSolidSphere(0.7, 22, 22);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glColor3f(0.45, 0.31, 0.09);
    glPushMatrix();
      glTranslatef(0, 18.5, 20);
      glScalef(8, 8, 12);
      glutSolidSphere(0.7, 22, 22);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
      glTranslatef(1.3, 22.5, 25);
      glScalef(1, 1, 1);
      glutSolidSphere(0.7, 22, 22);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
      glTranslatef(-1.3, 22.5, 25);
      glScalef(1, 1, 1);
      glutSolidSphere(0.7, 22, 22);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glColor3f(0.86, 0.28, 0.39);
      glTranslatef(0, 18.5, 28);
      glScalef(3, 2, 1);
      glutSolidSphere(0.7, 22, 22);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glColor3f(0.45, 0.31, 0.09);
    glPushMatrix();
      glTranslatef(0, 16.5, -19);
      glScalef(1, 5, 1);
      glutSolidSphere(0.7, 22, 22);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glColor3f(0.45, 0.31, 0.09);
    glPushMatrix();
      glTranslatef(1.8, 22.5, 19);
      glScalef(3, 5, 3);
      glutSolidSphere(0.7, 22, 22);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glColor3f(0.45, 0.31, 0.09);
    glPushMatrix();
      glTranslatef(-1.8, 22.5, 19);
      glScalef(3, 5, 3);
      glutSolidSphere(0.7, 22, 22);
    glPopMatrix();

    glPopMatrix();
    glPopMatrix();
}

//--------------------------------------------------------------------------------
void normal(float x1, float y1, float z1,
            float x2, float y2, float z2,
            float x3, float y3, float z3 )
{
    float nx, ny, nz;
    nx = y1*(z2-z3)+ y2*(z3-z1)+ y3*(z1-z2);
    ny = z1*(x2-x3)+ z2*(x3-x1)+ z3*(x1-x2);
    nz = x1*(y2-y3)+ x2*(y3-y1)+ x3*(y1-y2);
    glNormal3f(nx, ny, nz);
}

//--------------------------------------------------------------------------------

void drawVase()
{
    float wx[N], wy[N], wz[N];
    glColor4f(0.9, 0.33, 0.91, 1.0);
    for (int j= 0; j < 36; j++)
    {
        glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i < N; i++)
        {
            wx[i] = vx[i]*cos(skux) + vz[i]*sin(skux);
            wy[i] = vy[i];
            wz[i] = -vx[i]*sin(skux) + vz[i]*cos(skux);
            if (i > 0){normal(vx[i-1],vy[i-1],vz[i-1],vx[i],vy[i],vz[i], wx[i],wy[i],wz[i]);}

            glVertex3f(vx[i],vy[i],vz[i]);
            glVertex3f(wx[i],wy[i],wz[i]);
        }
        glEnd();
        for (int i = 0; i < N; i++)
        {
            vx[i] = wx[i];
            vy[i] = wy[i];
            vz[i] = wz[i];
        }
    }
}

//--------------------------------------------------------------------------------
void drawKirby()
{
    glPushMatrix();
    glColor3f(0.93, 0.62, 0.73);
    glPushMatrix();
      glTranslatef(0, 2.5, 0);
      glScalef(3, 3, 3);
      glTexCoord2f(0.0, 2.0);
      glutSolidSphere(0.7, 22, 22);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glColor3f(0.93, 0.62, 0.73);
    glPushMatrix();
      glTranslatef(2, 3 + theta * 0.05, 0);
      glScalef(1, 1, 1);
      glTexCoord2f(0.0, 2.0);
      glutSolidSphere(0.7, 22, 22);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glColor3f(0.93, 0.62, 0.73);
    glPushMatrix();
      glTranslatef(-2, 3 + theta * 0.05, 0);
      glScalef(1, 1, 1);
      glTexCoord2f(0.0, 2.0);
      glutSolidSphere(0.7, 22, 22);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glColor3f(0.88, 0.0, 0.36);
    glPushMatrix();
      glTranslatef(-1.5, 1, 1);
      glScalef(1, 1, 1.5);
      glTexCoord2f(0.0, 2.0);
      glutSolidSphere(0.7, 22, 22);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glColor3f(0.88, 0.0, 0.36);          //leg?2
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, txId[11]);
    glPushMatrix();
      glTranslatef(1.5, 1, 1);
      glScalef(1, 1, 1.5);
      glTexCoord2f(0.0, -2.0);
      glutSolidSphere(0.7, 22, 22);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glColor3f(0, 0, 0);          //leg?2
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, txId[11]);
    glPushMatrix();
      glTranslatef(0.5, 3.5, 2);
      glScalef(0.25, 0.6, 0.25);
      glTexCoord2f(0.0, -2.0);
      glutSolidSphere(0.7, 22, 22);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glColor3f(0, 0, 0);          //leg?2
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, txId[11]);
    glPushMatrix();
      glTranslatef(-0.5, 3.5, 2);
      glScalef(0.25, 0.6, 0.25);
      glTexCoord2f(0.0, -2.0);
      glutSolidSphere(0.7, 22, 22);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glColor3f(0.93, 0.24, 0.21);          //leg?2
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, txId[11]);
    glPushMatrix();
      glTranslatef(0, 2.5, 2);
      glScalef(0.5, 0.30, 0.25);
      glTexCoord2f(0.0, -2.0);
      glutSolidSphere(0.7, 22, 22);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glPopMatrix();
}
//--------------------------------------------------------------------------------
void myTimer(int value)
{
    theta += 1 * direction;
    if(theta > 20){
        theta = 19;
        direction = -1;
    } else if(theta < -20) {
        theta = -19;
        direction = 1;
    }
    count += 1;
    glutPostRedisplay();
    glutTimerFunc(50, myTimer, 0);
}

//--------------------------------------------------------------------------------
void drawPlane()
{

    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glTranslatef(20, 4 + (theta * 0.05), 20);
    glRotatef(135, 0, 1, 0);
    glColor3f(0.8, 0.12, 0.11);

    glPushMatrix();
      glTranslatef(0, 5.5, 0);
      glScalef(6, 3, 3);
      glTexCoord2f(0.0, 2.0);
      glutSolidSphere(0.7, 22, 22);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glColor3f(0.49, 0.49, 0.49);
    glPushMatrix();
      glTranslatef(-1, 7.5, 0);
      glScalef(4, 2, 2);
      glTexCoord2f(0.0, 2.0);
      glutSolidCube(1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glColor3f(0.49, 0.49, 0.49);
    glPushMatrix();
      glTranslatef(0, 5.5, 0);
      glScalef(5, 0.5, 9);
      glTexCoord2f(0.0, 2.0);
      glutSolidSphere(0.7, 22, 22);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
      glTranslatef(4, 5.5, 0);
      glRotatef(count * 50, 1, 0, 0);
      glScalef(0, 4, 0.5);
      glTexCoord2f(0.0, 2.0);
      glutSolidSphere(0.77, 22, 22);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
      glTranslatef(4, 5.5, 0);
      glRotatef(count * 50, 1, 0, 0);
      glScalef(0, 0.5, 4);
      glTexCoord2f(0.0, 2.0);
      glutSolidSphere(0.77, 22, 22);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
      glTranslatef(4, 5.4, 0);
      glScalef(0.4, 1, 1);
      glTexCoord2f(0.0, 2.0);
      glutSolidSphere(0.7, 22, 22);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

//--------------------------------------------------------------------------------
void drawChimney()
{
    glPushMatrix();
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
      glTranslatef(0, 5.5, -15);
      glScalef(3, 25, 3);
      glutSolidCube(1);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
//--------------------------------------------------------------------------------

void display()
{

    float lpos1[4] = {0, 0, 0, 1};
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45., 1., 1., 5000.);

    if(camf1 == 1){
        glPushMatrix();
        eye_y = 4 + theta* 0.05;
        glRotatef(theta, 0, 1, 0);
        glPopMatrix();
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye_x, eye_y, eye_z,  look_x, look_y, look_z,  0, 1, 0);
    glEnable(GL_DEPTH_TEST);
    glLightfv(GL_LIGHT0, GL_POSITION, lpos1);

    glPushMatrix();
    drawChimney();
    glPopMatrix();


    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,17, -14);
    glScalef(20,20,20);
    update_position();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1, 1.11, 1);
    floor1();
    glPopMatrix();
    drawAlienl();
    glPushMatrix();
    glRotatef(70, 0, 1, 0);
    glTranslatef(8, 1, -15);
    glScalef(0.5, 0.5, 0.5);
    drawKirby();
    glPopMatrix();
    drawPlane();
    drawDog();
    glPushMatrix();
    glTranslatef(-9.0, 3.5 + (theta * 0.1), 11);
    glScalef(0.1, 0.1, 0.1);
    drawVase();
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);

    floor();
    drawAlienl();
    walls();

    skybox();
    glFlush();
    roof();


    glutSwapBuffers();
}

//--------------------------------------------------------------------------------



int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH);
   glutInitWindowSize (1000, 1000);
   glutInitWindowPosition (10, 10);
   glutCreateWindow ("MBE84 COSC363 ASSIGNMENT");
   myTimer(0);
   initialise();

   glutDisplayFunc(display);
   glutSpecialFunc(special);
   glutMainLoop();
   return 0;
}
