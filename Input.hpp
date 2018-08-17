//
//  Input.hpp
//  CS155 Project
//
//  Created by Gus Callaway on 12/7/17.
//  Copyright © 2017 Gus Callaway. All rights reserved.
//

#ifndef Input_hpp
#define Input_hpp

#include "Camera.hpp"

class Input {
public:
    Input(Camera* camera);
    void ProcessKey(const char key, bool isPress);
    void ProcessMouse(int x, int y);
    // This function should be called every frame to
    // allow held keys to function properly.
    void Update();
    
    // Input shifts are just values in [0,1] that are
    // affected by pressing an up or down key. They can
    // be used to affect how the tunnel looks based on
    // user input.
    static const int numShifts = 5;
    float inputShifts[numShifts] = {0, 0.25, 0.5, 0, 0};
    // Rotation is different because it isn't bound to
    // [0, 1]. It controls what direction the tunnel
    // curves in.
    float rotation = 0;
    // This value is used for a simple key press trigger.
    // For that, we want to know how long ago the user
    // pressed the key. To allow for multiple presses
    // to be registered, we need an array. A value of
    // -1 in the array represents an open slot.
    static const int maxPresses = 100;
    float framesSincePress[maxPresses];
    bool paused = true;

private:
    Camera* camera;
    // 2 keys per shift plus 2 for rotation
    bool keysDown[numShifts*2 + 2];
    // Input sensitivities control how fast input shifts
    // change from frame to frame
    float inputSensitivities[numShifts] = {.0048, .003, .0048, .0048, .0048};
    float rotationSensitivity = .0048;
};

#endif /* Input_hpp */
