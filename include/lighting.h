#ifndef LIGHTING_H
#define LIGHTING_H

#include <GL/freeglut.h>
#include <cmath>
#include <vector>
using namespace std;

struct Label3D {
    float wx, wy, wz;
    const char* text;
    float r, g, b;
};

class LightingManager {
private:
    vector<Label3D> labelList;
    double g_mv[16], g_proj[16];
    int g_vp[4];
    float nebulaPhase;
    float planetGlowPhase[9];
    float sunPulse;
    bool showLabels;
    bool showOrbits;
    
public:
    LightingManager();
    ~LightingManager();
    
    void initLighting();
    void setupLighting();
    void drawStars();
    void drawSun();
    void drawGlow(float radius, float r, float g, float b, float pulse);
    void drawSphere(float radius, float r, float g, float b);
    void drawStripedSphere(float radius, int stacks, float r1, float g1, float b1, float r2, float g2, float b2);
    void drawOrbitRing(float radius, float r=1.0f, float g=1.0f, float b=1.0f, float a=0.18f);
    
    void addLabel(float x, float y, float z, const char* text, float r, float g, float b);
    void drawAllLabels();
    void captureMatrices();
    void setMatrices(double* mv, double* proj, int* vp);
    
    void toggleLabels() { showLabels = !showLabels; }
    void toggleOrbits() { showOrbits = !showOrbits; }
    bool getShowLabels() const { return showLabels; }
    bool getShowOrbits() const { return showOrbits; }
    
    void updatePhases(float delta);
    float getSunPulse() const { return sunPulse; }
    void setSunPulse(float p) { sunPulse = p; }
    float getNebulaPhase() const { return nebulaPhase; }
    void setNebulaPhase(float p) { nebulaPhase = p; }
    
    float* getPlanetGlowPhase() { return planetGlowPhase; }
};

#endif
