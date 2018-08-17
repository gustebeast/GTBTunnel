//
//  Camera.cpp
//  CS155 Project
//
//  Created by Gus Callaway on 10/29/17.
//  Copyright © 2017 Gus Callaway. All rights reserved.
//

#include "Camera.hpp"
#include "findGLUT.h"

void Camera::Move(float tunnelSectionWidth) {
    position.z += speed*2;
    // Since things can get wonky when the camera's z value
    // gets too big, reset it back to zero when it lines
    // up with the section width
    if (position.z > 1000 && (int)position.z % (int)tunnelSectionWidth == 0)
        position.z = 0;

    this->Look();
}

void Camera::Look() {
    // Calculate z shift value for target point to make
    // the target a point on a sphere around the camera
    float z = sqrt(4 - target.x*target.x - target.y*target.y);
    gluLookAt(position.x, position.y, position.z,
              target.x, target.y, position.z + z,
              0.0, 1.0, 0.0);
}
