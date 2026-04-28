
#ifndef SOLAR_SYSTEM_H
#define SOLAR_SYSTEM_H

#include <GL/freeglut.h>
#include <vector>

#define PI 3.14159265358979323846f

struct Asteroid{
float angle;
float radius;
float yOff;
float size;
};

extern std::vector<Asteroid> asteroids;

extern float speedMultiplier;
extern bool paused;

extern float earthAngle,marsAngle,venusAngle,mercuryAngle;
extern float jupiterAngle,saturnAngle,uranusAngle,neptuneAngle;

extern float moonAngle,phobosAngle,deimosAngle;
extern float titaniaAngle,oberonAngle,tritonAngle;

extern float sunRotation;
extern float earthRotation;
extern float marsRotation;
extern float jupiterRotation;

extern float asteroidAngle;
extern float sunPulse;

void initAsteroids();

void drawOrbitRing(float radius,
float r=1,float g=1,float b=1,float a=0.18);

void drawSphere(float radius,float r,float g,float b);

void drawStripedSphere(float radius,int stacks,
float r1,float g1,float b1,
float r2,float g2,float b2);

void drawSun();

void drawMercury();
void drawVenus();
void drawEarthSystem();
void drawMarsSystem();

void drawJupiter();
void drawSaturn();
void drawUranus();
void drawNeptune();

void drawAsteroidBelt();

void display();

void update(int value);

#endif