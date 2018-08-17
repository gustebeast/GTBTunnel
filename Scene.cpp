//
//  Renderer.cpp
//  CS155 Project
//
//  Created by Gus Callaway on 10/29/17.
//  Copyright © 2017 Gus Callaway. All rights reserved.
//

#include "Scene.hpp"
#include "findGLUT.h"

Scene::Scene(Camera* camera,
             Input* input,
             Tunnel* tunnel,
             SimpleShaderProgram* shader)
: camera(camera), input(input), tunnel(tunnel), shader(shader) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

void Scene::Draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_FLAT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    camera->speed = input->inputShifts[1];
    camera->Move(tunnel->numStripWidthsPerSpiral*tunnel->stripWidth);
    shader->Bind();
    shader->SetUniform("cameraPos", camera->position.x, camera->position.y, camera->position.z, 1);
    shader->SetUniform("frame", this->frame++);
    shader->SetUniform1fv("inputShifts", input->inputShifts, input->numShifts);
    shader->SetUniform("rotation", input->rotation);
    shader->SetUniform1fv("framesSincePress", input->framesSincePress, input->maxPresses);
    tunnel->stripWidth = input->inputShifts[2] + 0.5;
    tunnel->Draw(camera->position.z);
    if (input->paused) this->DrawPauseMenu();
    shader->UnBind();
    glutSwapBuffers();
}

void Scene::DrawPauseMenu() {
    float z = camera->position.z + 20;
    glBegin(GL_QUADS);
    // Let the shader know this is the pause menu background
    glNormal3f(-1, 1, 0);
    glVertex3f(-5.25, -3.5, z);
    glVertex3f(-5.25,  3.5, z);
    glVertex3f( 5.25,  3.5, z);
    glVertex3f( 5.25, -3.5, z);
    glEnd();
    this->DrawStrokeText("Welcome to the GTB Tunnel", 0.004, 3.8, 2.3, z - 1);
    this->DrawStrokeText("controls:", 0.003, 3, 1, z - 1);
    this->DrawStrokeText("W/S   - Tunnel bend strength", 0.0015, 2.5, 0.6, z - 1);
    this->DrawStrokeText("A/D   - Tunnel bend direction", 0.0015, 2.5, 0.2, z - 1);
    this->DrawStrokeText("R/F   - Speed", 0.0015, 2.5, -0.2, z - 1);
    this->DrawStrokeText("T/G   - Wall triangle size", 0.0015, 2.5, -.6, z - 1);
    this->DrawStrokeText("Y/H   - Line-ification", 0.0015, 2.5, -1, z - 1);
    this->DrawStrokeText("U/J   - Blue-ification", 0.0015, 2.5, -1.4, z - 1);
    this->DrawStrokeText("MOUSE - Look around", 0.0015, 2.5, -1.8, z - 1);
    this->DrawStrokeText("Space - Trigger displacement wave", 0.0015, 2.5, -2.2, z - 1);
    this->DrawStrokeText("ESC   - Toggle pause menu", 0.0015, 2.5, -2.6, z - 1);
}

void Scene::DrawStrokeText(std::string string, float scale, float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(-scale, scale, 0);
    // Let the shader know this is the pause menu text
    glNormal3f(-1, -1, 0);
    for (char c : string)
    {
        if (scale < .003) {
            glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN , c);
        } else {
            glutStrokeCharacter(GLUT_STROKE_ROMAN , c);
        }
        
    }
    glPopMatrix();
}

void Scene::ReshapeCallback(int w, int h){
    glViewport(0, 0, w, h);
    
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(30.0f, (float)w/(float)h, 0.1f, 100000.f);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
