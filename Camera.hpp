//
//  Camera.hpp
//  CS155 Project
//
//  Created by Gus Callaway on 10/29/17.
//  Copyright © 2017 Gus Callaway. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include "util.h"

class Camera {
public:
    void Move(float tunnelSectionWidth);
    void Look();
    
    Vec3f position = Vec3f(0, 0, 5);
    // Target z value is computed on the fly
    // based on camera position: see Look()
    Vec3f target = Vec3f(0, 0, 0);
    float speed = .5; // how fast the camera moves forward
};

#endif /* Camera_hpp */
