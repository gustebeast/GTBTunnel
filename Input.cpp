//
//  Input.cpp
//  CS155 Project
//
//  Created by Gus Callaway on 12/7/17.
//  Copyright © 2017 Gus Callaway. All rights reserved.
//

#include "Input.hpp"
#include "findGLUT.h"

Input::Input(Camera* camera) : camera(camera) {
    // Initialize arrays with default values
    for (int i = 0; i < numShifts*2 + 2; i++)
        keysDown[i] = false;
    for (int i = 0; i < maxPresses; i++)
        framesSincePress[i] = -1;
}

void Input::Update() {
    // If a key is down that controls a shift value,
    // adjust that shift value every frame, but stay
    // within the range [0, 1]
    for (int i = 0; i < numShifts; i++) {
        if (keysDown[i*2]) {
            inputShifts[i] = fmin(inputShifts[i] + inputSensitivities[i], 1);
        }
        if (keysDown[i*2 + 1]) {
            inputShifts[i] = fmax(inputShifts[i] - inputSensitivities[i], 0);
        }
    }
    // The last two keys control rotation and are
    // delt with seperately because there are no
    // bounds on the value
    if (keysDown[numShifts*2]) {
        rotation += rotationSensitivity;
    }
    if (keysDown[numShifts*2 + 1]) {
        rotation -= rotationSensitivity;
    }
    // Finally we update the framesSincePress array
    // to make sure all events triggered by presses
    // are continuing through time
    for (int i = 0; i < maxPresses; i++) {
        if (framesSincePress[i] > 220) {
            // After a certain period of time we forget
            // about this press to allow for another one
            // to take its place
            framesSincePress[i] = -1;
        }
        if (framesSincePress[i] != -1) {
            framesSincePress[i]++;
        }
    }
    
}

void Input::ProcessKey(const char key, bool isPress) {
    // First handle keys that require press and hold
    switch(key) {
        case 'w':
            keysDown[0] = isPress;
            return;
        case 's':
            keysDown[1] = isPress;
            return;
        case 'r':
            keysDown[2] = isPress;
            return;
        case 'f':
            keysDown[3] = isPress;
            return;
        case 't':
            keysDown[4] = isPress;
            return;
        case 'g':
            keysDown[5] = isPress;
            return;
        case 'y':
            keysDown[6] = isPress;
            return;
        case 'h':
            keysDown[7] = isPress;
            return;
        case 'u':
            keysDown[8] = isPress;
            return;
        case 'j':
            keysDown[9] = isPress;
            return;
        case 'd':
            keysDown[10] = isPress;
            return;
        case 'a':
            keysDown[11] = isPress;
            return;
    }
    // Now handle keys that just require press
    if (isPress) {
        switch(key) {
            case ' ':
                // Find a slot in the array where we
                // can save a hit of the space bar
                for (int i = 0; i < maxPresses; i++) {
                    if (framesSincePress[i] == -1) {
                        framesSincePress[i] = 0;
                        return;
                    }
                }
                return;
            case 27: // escape key
                paused = !paused;
                if (paused) {
                    glutSetCursor(GLUT_CURSOR_INHERIT);
                } else {
                    glutSetCursor(GLUT_CURSOR_NONE);
                }
                return;
        }
    }
}

void Input::ProcessMouse(int x, int y) {
    // Take screen space x and y coordinates
    // and translate them into world space
    // coordiantes for the camera to look at.
    // The z value is ignored by the camera
    Vec3f newTarget = camera->target;
    newTarget.x = x / float(glutGet(GLUT_WINDOW_WIDTH));
    newTarget.y = y / float(glutGet(GLUT_WINDOW_HEIGHT));
    if (newTarget.x < 0 || newTarget.x > 1 || newTarget.y < 0 || newTarget.y > 1)
        newTarget = Vec3f(0.5, 0.5, newTarget.z);
    newTarget -= Vec3f(0.5, 0.5, 0);
    newTarget *= Vec3f(-3, -2, 1);
    camera->target = newTarget;
}

