// ============================================================
//  camera.cpp  –  Camera state & control implementation
//  Solar System Simulation | CG Project 2026
//  BS-IT 6th Semester | Faiza, Hadiqa, Mahnoor
// ============================================================

#include "../include/camera.h"
#include <GL/freeglut.h>
#include <cmath>

#ifndef PI
#define PI 3.14159265358979323846f
#endif

// ============================================================
//  CAMERA STATE  (definitions)
// ============================================================
float camAngleX   =  25.0f;   // Pitch  – start looking slightly down
float camAngleY   =   0.0f;   // Yaw
float camZoom     =  65.0f;   // Distance from origin

bool  flybyActive =  false;
float flybyTime   =   0.0f;

// ============================================================
//  cameraApply
//  Compute camera eye position from spherical coords and call
//  gluLookAt. Must be called after glLoadIdentity() each frame.
// ============================================================
void cameraApply()
{
    float camX = camZoom * sinf(camAngleY * PI / 180.0f)
                         * cosf(camAngleX * PI / 180.0f);
    float camY = camZoom * sinf(camAngleX * PI / 180.0f);
    float camZ = camZoom * cosf(camAngleY * PI / 180.0f)
                         * cosf(camAngleX * PI / 180.0f);

    gluLookAt(camX, camY, camZ,
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);
}

// ============================================================
//  cameraRotate  –  apply yaw / pitch deltas with clamping
// ============================================================
void cameraRotate(float deltaYaw, float deltaPitch)
{
    camAngleY += deltaYaw;
    camAngleX += deltaPitch;

    // Clamp pitch so camera never flips upside-down
    if (camAngleX > CAM_PITCH_MAX) camAngleX = CAM_PITCH_MAX;
    if (camAngleX < CAM_PITCH_MIN) camAngleX = CAM_PITCH_MIN;
}

// ============================================================
//  cameraZoom  –  move camera closer / farther
// ============================================================
void cameraZoom(float delta)
{
    camZoom += delta;

    if (camZoom < CAM_ZOOM_MIN) camZoom = CAM_ZOOM_MIN;
    if (camZoom > CAM_ZOOM_MAX) camZoom = CAM_ZOOM_MAX;
}

// ============================================================
//  cameraReset  –  restore defaults
// ============================================================
void cameraReset()
{
    camAngleX   =  25.0f;
    camAngleY   =   0.0f;
    camZoom     =  65.0f;
    flybyActive = false;
    flybyTime   =   0.0f;
}

// ============================================================
//  cameraToggleFlyby  –  enable / disable cinematic flyby
// ============================================================
void cameraToggleFlyby()
{
    flybyActive = !flybyActive;
    if (flybyActive)
        flybyTime = 0.0f;   // restart path from beginning
}

// ============================================================
//  cameraUpdateFlyby
//  A smooth figure-8 cinematic path around the solar system.
//  Call once per timer tick when flybyActive == true.
//
//  The path uses a Lissajous-style parametric curve so the
//  camera smoothly visits different vantage points:
//    yaw   = slow continuous orbit
//    pitch = gentle oscillation up/down
//    zoom  = breathing in/out between close and wide shots
// ============================================================
void cameraUpdateFlyby(float speedMult)
{
    if (!flybyActive) return;

    // Advance time (radians per tick, scaled by speed)
    flybyTime += 0.004f * speedMult;

    // Yaw: full slow orbit
    camAngleY = flybyTime * (180.0f / PI);       // degrees

    // Pitch: oscillate between -30° and +45°
    camAngleX = 7.5f + 37.5f * sinf(flybyTime * 0.4f);

    // Zoom: breathe between 40 and 110
    camZoom = 75.0f + 35.0f * sinf(flybyTime * 0.25f);

    // Clamp just in case
    if (camAngleX > CAM_PITCH_MAX) camAngleX = CAM_PITCH_MAX;
    if (camAngleX < CAM_PITCH_MIN) camAngleX = CAM_PITCH_MIN;
    if (camZoom   < CAM_ZOOM_MIN)  camZoom   = CAM_ZOOM_MIN;
    if (camZoom   > CAM_ZOOM_MAX)  camZoom   = CAM_ZOOM_MAX;
}
