//
//  Scene.hpp
//  CS155 Project
//
//  Created by Gus Callaway on 10/29/17.
//  Copyright © 2017 Gus Callaway. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <stdio.h>
#include <vector>
#include "Camera.hpp"
#include "Input.hpp"
#include "Tunnel.hpp"
#include "SimpleShaderProgram.h"

class Scene {
public:
    Scene(Camera* camera,
          Input* input,
          Tunnel* tunnel,
          SimpleShaderProgram* shader);
    void Draw();
    void ReshapeCallback(int w, int h);
    
private:
    void DrawPauseMenu();
    void DrawStrokeText(std::string string, float scale, float x, float y, float z);
    Camera* camera;
    Input* input;
    Tunnel* tunnel;
    SimpleShaderProgram* shader;

    float frame = 0;
};

#endif /* Scene_hpp */
