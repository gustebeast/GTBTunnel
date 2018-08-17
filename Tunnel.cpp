//
//  Tunnel.cpp
//  CS155 Project
//
//  Created by Gus Callaway on 10/28/17.
//  Copyright © 2017 Gus Callaway. All rights reserved.
//

#include "Tunnel.hpp"
#include <fstream>
#include <stdlib.h>
#include "util.h"

void Tunnel::Draw(float cameraZPos) {
    // Calculate a starting position that only updates in
    // chunks of section widths so the tunnel looks like it
    // is moving past the camera
    float sectionWidth = stripWidth*numStripWidthsPerSpiral;
    startingZ = floorf(cameraZPos/sectionWidth - 1) * sectionWidth;
    float pi = 3.141592654;
    float x, y, z, theta, sectionZ, stripZ;
    int triangleNum = 0;
    // A section is a group of strips that together form a smooth wall
    for (int section = 0; section < numSections; section++) {
        // Shift the starting Z a strip length forward for each section
        sectionZ = startingZ + section*sectionWidth;
        // Draw a group of strips that will fuse to form a solid section
        for (int strip = 0; strip < numStripWidthsPerSpiral; strip++) {
            //srand(strip);
            glBegin(GL_TRIANGLE_STRIP);
            // Each strip is drawn one strip width beyond the previous
            stripZ = sectionZ + strip*stripWidth;
            // A strip is one slice of the overall cylinder. Simply it could
            // just be a thin cylinder, but they are usually stretched in the
            // z direction to give a more tunnel like look.
            for (int step = 0; step < numSteps + 2; step++) {
                // Shift the step a bit to get the triangles to line up
                int shiftedStep = step + strip;
                theta = shiftedStep*2*pi/numSteps;
                x = radius*cos(theta);
                y = radius*sin(theta);
                // Z value starts at the strip's starting z, then moves forward
                // by the current step times the strip's total length divided by
                // the total number of steps
                z = stripZ + shiftedStep*sectionWidth/numSteps;
                // Every other vertex is shifted by the width of the strip
                if (step % 2 == 1) {
                    z += stripWidth;
                }
                srand(x + y + z);
                glVertex3f(x, y, z);
                glNormal3f(triangleNum++, rand() % 100, rand() % 100);
            }
            glEnd();
        }
    }
}
