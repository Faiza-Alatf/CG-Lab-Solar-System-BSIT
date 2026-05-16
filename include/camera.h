#pragma once
// ============================================================
//  camera.h  –  Camera state & control declarations
//  Solar System Simulation | CG Project 2026
//  BS-IT 6th Semester | Faiza, Hadiqa, Mahnoor
// ============================================================

#ifndef CAMERA_H
#define CAMERA_H

// ============================================================
//  CAMERA STATE  (extern – defined in camera.cpp)
// ============================================================
extern float camAngleX;      // Pitch  (vertical tilt, degrees)
extern float camAngleY;      // Yaw    (horizontal rotation, degrees)
extern float camZoom;        // Distance from origin

// Flyby / cinematic mode
extern bool  flybyActive;
extern float flybyTime;      // Accumulated time for flyby path

// Clamp limits
static const float CAM_PITCH_MIN  = -85.0f;
static const float CAM_PITCH_MAX  =  85.0f;
static const float CAM_ZOOM_MIN   =  12.0f;
static const float CAM_ZOOM_MAX   = 160.0f;

// ============================================================
//  CAMERA FUNCTIONS
// ============================================================

/**
 * Apply the camera view transform.
 * Call once per frame inside display() AFTER glLoadIdentity().
 */
void cameraApply();

/**
 * Rotate camera by delta angles (degrees).
 *   deltaYaw   – positive = rotate right
 *   deltaPitch – positive = tilt down
 */
void cameraRotate(float deltaYaw, float deltaPitch);

/**
 * Zoom camera by a delta distance.
 *   delta > 0 → zoom out
 *   delta < 0 → zoom in
 */
void cameraZoom(float delta);

/**
 * Reset camera to default position.
 */
void cameraReset();

/**
 * Enable / disable the automatic flyby mode.
 */
void cameraToggleFlyby();

/**
 * Advance flyby animation by one tick.
 * Call from the animation update loop when flyby is active.
 */
void cameraUpdateFlyby(float speedMult);

#endif // CAMERA_H
