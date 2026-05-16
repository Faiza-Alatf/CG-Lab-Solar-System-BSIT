// ============================================================
//  input.cpp  –  Keyboard, special-key & mouse callbacks
//  Solar System Simulation | CG Project 2026
//  BS-IT 6th Semester | Faiza, Hadiqa, Mahnoor
//
//  HOW TO USE IN main.cpp / solar.cpp
//  -----------------------------------
//  1.  #include "input.h"   (or declare externs for the globals)
//  2.  Call inputRegisterCallbacks() once in main() BEFORE
//      glutMainLoop():
//          inputRegisterCallbacks();
//  3.  The callbacks read/write the shared globals below, which
//      are also used by camera.cpp and your animation loop.
// ============================================================

#include "../include/camera.h"
#include <GL/freeglut.h>
#include <cmath>
#include <cstdlib>   // exit()

// ============================================================
//  SHARED ANIMATION GLOBALS
//  (extern declarations – must be defined in your main file)
// ============================================================
extern float speedMultiplier;
extern bool  paused;

// Orbital angles – needed for Reset
extern float earthAngle, marsAngle, venusAngle, mercuryAngle;
extern float jupiterAngle, saturnAngle, uranusAngle, neptuneAngle;
extern float moonAngle, phobosAngle, deimosAngle;
extern float titaniaAngle, oberonAngle, tritonAngle;
extern float asteroidAngle, sunPulse;

// ============================================================
//  MOUSE DRAG STATE  (private to this translation unit)
// ============================================================
static int  lastMouseX = 0;
static int  lastMouseY = 0;
static bool mouseDown  = false;

// ============================================================
//  KEYBOARD CALLBACK
//  Keys:
//    P / p        – Pause / Resume
//    + / =        – Speed up   (max 10×)
//    - / _        – Slow down  (min 0.5×)
//    R / r        – Reset all angles & camera
//    F / f        – Toggle cinematic flyby
//    ESC          – Quit
// ============================================================
void keyboardCallback(unsigned char key, int /*x*/, int /*y*/)
{
    switch (key)
    {
        // --- Pause / Resume ---
        case 'p': case 'P':
            paused = !paused;
            break;

        // --- Speed Up ---
        case '+': case '=':
            speedMultiplier = fminf(speedMultiplier + 0.5f, 10.0f);
            break;

        // --- Slow Down ---
        case '-': case '_':
            speedMultiplier = fmaxf(speedMultiplier - 0.5f, 0.5f);
            break;

        // --- Reset everything ---
        case 'r': case 'R':
            // Planet orbital angles
            earthAngle = marsAngle = venusAngle = mercuryAngle = 0.0f;
            jupiterAngle = saturnAngle = uranusAngle = neptuneAngle = 0.0f;
            // Moon angles
            moonAngle = phobosAngle = deimosAngle = 0.0f;
            titaniaAngle = oberonAngle = tritonAngle = 0.0f;
            // Misc
            asteroidAngle  = 0.0f;
            sunPulse       = 0.0f;
            // Animation state
            speedMultiplier = 1.0f;
            paused          = false;
            // Camera
            cameraReset();
            break;

        // --- Flyby mode toggle ---
        case 'f': case 'F':
            cameraToggleFlyby();
            break;

        // --- Quit ---
        case 27:   // ESC
            exit(0);
            break;

        default:
            break;
    }

    glutPostRedisplay();
}

// ============================================================
//  SPECIAL KEYS CALLBACK  (arrow keys)
//  Arrow keys rotate the camera when flyby is NOT active.
//  Step size: 3 degrees per key press.
// ============================================================
void specialKeysCallback(int key, int /*x*/, int /*y*/)
{
    if (flybyActive) return;   // arrow keys disabled during flyby

    const float STEP = 3.0f;

    switch (key)
    {
        case GLUT_KEY_UP:    cameraRotate( 0.0f, -STEP); break;
        case GLUT_KEY_DOWN:  cameraRotate( 0.0f,  STEP); break;
        case GLUT_KEY_LEFT:  cameraRotate(-STEP,  0.0f); break;
        case GLUT_KEY_RIGHT: cameraRotate( STEP,  0.0f); break;
        default: break;
    }

    glutPostRedisplay();
}

// ============================================================
//  MOUSE BUTTON CALLBACK
//  Left button  – start / stop drag tracking
//  Scroll up    – zoom in
//  Scroll down  – zoom out
// ============================================================
void mouseCallback(int button, int state, int x, int y)
{
    // Left button drag tracking
    if (button == GLUT_LEFT_BUTTON)
    {
        mouseDown  = (state == GLUT_DOWN);
        lastMouseX = x;
        lastMouseY = y;
    }

    // Mouse wheel zoom (GLUT maps wheel to buttons 3 & 4)
    if (button == 3) { cameraZoom(-2.5f); glutPostRedisplay(); }
    if (button == 4) { cameraZoom( 2.5f); glutPostRedisplay(); }
}

// ============================================================
//  MOUSE MOTION CALLBACK  (drag to orbit camera)
//  Sensitivity: 0.5 degrees per pixel.
//  Flyby is automatically cancelled when the user drags.
// ============================================================
void mouseMotionCallback(int x, int y)
{
    if (!mouseDown) return;

    // Cancel flyby so the user regains manual control
    if (flybyActive) flybyActive = false;

    float deltaX = (float)(x - lastMouseX);
    float deltaY = (float)(y - lastMouseY);

    cameraRotate(deltaX * 0.5f, deltaY * 0.5f);

    lastMouseX = x;
    lastMouseY = y;

    glutPostRedisplay();
}

// ============================================================
//  inputRegisterCallbacks
//  Call this once in main() before glutMainLoop().
// ============================================================
void inputRegisterCallbacks()
{
    glutKeyboardFunc   (keyboardCallback);
    glutSpecialFunc    (specialKeysCallback);
    glutMouseFunc      (mouseCallback);
    glutMotionFunc     (mouseMotionCallback);
}
