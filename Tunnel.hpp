//
//  Tunnel.hpp
//  CS155 Project
//
//  Created by Gus Callaway on 10/28/17.
//  Copyright © 2017 Gus Callaway. All rights reserved.
//

#ifndef Tunnel_hpp
#define Tunnel_hpp

#include <vector>
#include <stdio.h>
#include "util.h"
#include "SimpleShaderProgram.h"
#include "Camera.hpp"

class Tunnel {
public:
    void Draw(float cameraZPos);

    float stripWidth = 1;
    int numStripWidthsPerSpiral = 20; // Distance traveled per spiral
    int numSteps =  100; // Num vertices per strip
    int numSections = 30;
    float radius = 10;
    
private:
    float startingZ;
};

#endif /* Tunnel_hpp */
