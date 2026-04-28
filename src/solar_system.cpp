
#include "../include/solar_system.h"
#include <cmath>
#include <cstdio>

using namespace std;

vector<Asteroid> asteroids;

float speedMultiplier=1.0;
bool paused=false;

float earthAngle=0;
float marsAngle=0;
float venusAngle=0;
float mercuryAngle=0;

float jupiterAngle=0;
float saturnAngle=0;
float uranusAngle=0;
float neptuneAngle=0;

float moonAngle=0;
float phobosAngle=0;
float deimosAngle=0;

float titaniaAngle=0;
float oberonAngle=0;
float tritonAngle=0;

float sunRotation=0;
float earthRotation=0;
float marsRotation=0;
float jupiterRotation=0;

float asteroidAngle=0;
float sunPulse=0;

void drawOrbitRing(float radius,float r,float g,float b,float a)
{
glDisable(GL_LIGHTING);

glColor4f(r,g,b,a);

glBegin(GL_LINE_LOOP);

for(int i=0;i<720;i++)
{
float rad=i*PI/360;
glVertex3f(radius*cos(rad),0,radius*sin(rad));
}

glEnd();

glEnable(GL_LIGHTING);
}

void drawSphere(float radius,float r,float g,float b)
{
glColor3f(r,g,b);
glutSolidSphere(radius,48,48);
}

void initAsteroids()
{
srand(777);

for(int i=0;i<320;i++)
{
Asteroid a;

a.angle=(rand()%3600)/10.0;
a.radius=27+(rand()%400)/100.0;
a.yOff=((rand()%100)-50)/200.0;
a.size=0.04+(rand()%8)/100.0;

asteroids.push_back(a);
}
}

void drawAsteroidBelt()
{
for(int i=0;i<asteroids.size();i++)
{
float ang=(asteroids[i].angle+asteroidAngle)*PI/180;

float x=asteroids[i].radius*cos(ang);
float z=asteroids[i].radius*sin(ang);

glPushMatrix();

glTranslatef(x,asteroids[i].yOff,z);

glutSolidSphere(
asteroids[i].size,
4,
4
);

glPopMatrix();

}
}