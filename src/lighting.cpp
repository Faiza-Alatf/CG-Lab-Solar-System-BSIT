#include "lighting.h"
#include <cstdio>
#include <cstdlib>

#define PI 3.14159265358979323846f

LightingManager::LightingManager()
    : nebulaPhase(0.0f), sunPulse(0.0f), showLabels(true), showOrbits(true)
{
    for (int i = 0; i < 9; i++) planetGlowPhase[i] = 0.0f;
}

LightingManager::~LightingManager() {}

void LightingManager::initLighting()
{
    setupLighting();
}

void LightingManager::setupLighting()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    GLfloat lightPos[]      = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat lightAmbient[]  = { 0.07f, 0.06f, 0.04f, 1.0f };
    GLfloat lightDiffuse[]  = { 1.0f,  0.96f, 0.84f, 1.0f };
    GLfloat lightSpecular[] = { 1.0f,  1.0f,  0.9f,  1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,  1.0f);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION,    0.004f);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.00015f);

    GLfloat matSpec[] = { 0.45f, 0.45f, 0.45f, 1.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
    glMaterialf (GL_FRONT, GL_SHININESS, 45.0f);
    glShadeModel(GL_SMOOTH);
}

void LightingManager::drawSphere(float radius, float r, float g, float b)
{
    glColor3f(r, g, b);
    glutSolidSphere(radius, 48, 48);
}

void LightingManager::drawStripedSphere(float radius, int stacks, float r1, float g1, float b1, float r2, float g2, float b2)
{
    for (int i = 0; i < stacks; i++) {
        float t = (float)i / stacks;
        if (i % 2 == 0) glColor3f(r1, g1, b1);
        else             glColor3f(r2, g2, b2);
        float phi1 = PI * (t - 0.5f);
        float phi2 = PI * (t + 1.0f/stacks - 0.5f);
        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= 48; j++) {
            float theta = 2.0f * PI * j / 48.0f;
            float cp1 = cosf(phi1), sp1 = sinf(phi1);
            float cp2 = cosf(phi2), sp2 = sinf(phi2);
            float ct  = cosf(theta), st = sinf(theta);
            glNormal3f(ct*cp1, sp1, st*cp1);
            glVertex3f(radius*ct*cp1, radius*sp1, radius*st*cp1);
            glNormal3f(ct*cp2, sp2, st*cp2);
            glVertex3f(radius*ct*cp2, radius*sp2, radius*st*cp2);
        }
        glEnd();
    }
}

void LightingManager::drawGlow(float radius, float r, float g, float b, float pulse)
{
    glDisable(GL_LIGHTING);
    float glow = radius * 1.35f + 0.08f * sinf(pulse);
    glColor4f(r, g, b, 0.10f);
    glutSolidSphere(glow, 16, 16);
    glColor4f(r, g, b, 0.06f);
    glutSolidSphere(glow * 1.2f, 12, 12);
    glEnable(GL_LIGHTING);
}

void LightingManager::drawOrbitRing(float radius, float r, float g, float b, float a)
{
    if (!showOrbits) return;
    glDisable(GL_LIGHTING);
    glColor4f(r, g, b, a);
    glLineStipple(1, 0xAAAA);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 720; i++) {
        float rad = i * PI / 360.0f;
        glVertex3f(radius * cosf(rad), 0.0f, radius * sinf(rad));
    }
    glEnd();
    glDisable(GL_LINE_STIPPLE);
    glEnable(GL_LIGHTING);
}

void LightingManager::drawStars()
{
    glDisable(GL_LIGHTING);

    float nb = 0.03f + 0.015f * sinf(nebulaPhase * 0.01f);
    glColor4f(0.15f, 0.05f, nb * 3.0f, 0.04f);
    glPushMatrix(); glTranslatef(-80, 30, -150); glutSolidSphere(55, 8, 8); glPopMatrix();
    glColor4f(nb, 0.04f, 0.12f, 0.03f);
    glPushMatrix(); glTranslatef(120, -40, -180); glutSolidSphere(70, 8, 8); glPopMatrix();

    glPointSize(2.2f);
    glBegin(GL_POINTS);
    srand(42);
    for (int i = 0; i < 1500; i++) {
        float x = ((rand() % 500) - 250) * 1.0f;
        float y = ((rand() % 500) - 250) * 1.0f;
        float z = ((rand() % 500) - 250) * 1.0f;
        if (fabsf(x) < 80 && fabsf(y) < 80 && fabsf(z) < 80) x += 130.0f;
        float twinkle = 0.7f + 0.3f * sinf(nebulaPhase * 0.05f + i * 0.37f);
        int type = rand() % 6;
        if      (type == 0) glColor4f(1.0f, 0.85f, 0.7f, twinkle);
        else if (type == 1) glColor4f(0.7f, 0.8f, 1.0f, twinkle);
        else if (type == 2) glColor4f(1.0f, 0.9f, 0.5f, twinkle * 0.8f);
        else                glColor4f(1.0f, 1.0f, 1.0f, twinkle);
        glVertex3f(x, y, z);
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

void LightingManager::drawSun()
{
    glDisable(GL_LIGHTING);
    float glowSize = 4.3f + 0.18f * sinf(sunPulse * 0.05f);

    glColor4f(1.0f, 0.45f, 0.02f, 0.04f); glutSolidSphere(glowSize + 1.5f, 16, 16);
    glColor4f(1.0f, 0.55f, 0.05f, 0.07f); glutSolidSphere(glowSize + 0.9f, 20, 20);
    glColor4f(1.0f, 0.65f, 0.1f,  0.12f); glutSolidSphere(glowSize + 0.3f, 24, 24);

    glEnable(GL_LIGHTING);
}

void LightingManager::addLabel(float x, float y, float z, const char* text, float r, float g, float b)
{
    if (!showLabels) return;
    Label3D l;
    l.wx = x; l.wy = y; l.wz = z;
    l.text = text;
    l.r = r; l.g = g; l.b = b;
    labelList.push_back(l);
}

void LightingManager::drawAllLabels()
{
    if (!showLabels || labelList.empty()) return;

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, g_vp[2], 0, g_vp[3]);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    for (int i = 0; i < (int)labelList.size(); i++) {
        double sx, sy, sz;

        gluProject(labelList[i].wx, labelList[i].wy, labelList[i].wz,
                   g_mv, g_proj, g_vp, &sx, &sy, &sz);

        if (sz < 0.0 || sz > 1.0) continue;

        sy = g_vp[3] - sy;

        glColor3f(labelList[i].r, labelList[i].g, labelList[i].b);
        glRasterPos2f((float)sx, (float)sy);

        for (const char* c = labelList[i].text; *c; c++)
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    labelList.clear();
}

void LightingManager::captureMatrices()
{
    glGetDoublev(GL_MODELVIEW_MATRIX,  g_mv);
    glGetDoublev(GL_PROJECTION_MATRIX, g_proj);
    glGetIntegerv(GL_VIEWPORT,         g_vp);
}

void LightingManager::setMatrices(double* mv, double* proj, int* vp)
{
    for (int i = 0; i < 16; i++) {
        g_mv[i] = mv[i];
        g_proj[i] = proj[i];
    }
    for (int i = 0; i < 4; i++) g_vp[i] = vp[i];
}

void LightingManager::updatePhases(float delta)
{
    sunPulse += delta;
    nebulaPhase += delta;
    for (int i = 1; i <= 8; i++) {
        planetGlowPhase[i] += 0.05f * delta;
    }
}
