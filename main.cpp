#include "main.h"
#ifdef WIN32
#define ssize_t SSIZE_T
#endif

#include <vector>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include "Camera.hpp"
#include "Input.hpp"
#include "Scene.hpp"

float illumColors[9] = {
    0.1, 0.1, 0.1,  // ambient
    0.5, 0.5, 0.5,  // diffuse
    0.5, 0.5, 0.5   // specular
};
float matColors[9] = {
    1.0, 215.0/255, 0.0,  // ambient
    1.0, 215.0/255, 0.0,  // diffuse
    1.0, 1.0, 1.0   // specular
};
Vec3f lightPos = Vec3f(0, 3, 3);
float shine = 5;
float frameRate = 60; // also in Camera.cpp

Input* inputPointer;
Scene* scenePointer;

void DisplayFunc() {
    inputPointer->Update();
    scenePointer->Draw();
}

void ReshapeFunc(int w, int h) {
    scenePointer->ReshapeCallback(w, h);
}

void KeyboardFunc(unsigned char key, int x, int y) {
    inputPointer->ProcessKey(key, true);
    glutPostRedisplay();
}

void KeyboardUpFunc(unsigned char key, int x, int y) {
    inputPointer->ProcessKey(key, false);
    glutPostRedisplay();
}

void MouseMotionFunc(int x, int y) {
    inputPointer->ProcessMouse(x, y);
    glutPostRedisplay();
}

void FrameTimer(int) {
    DisplayFunc();
    glutTimerFunc(1000/frameRate, FrameTimer, 0);
}

void NoOp() {}

int main(int argc, char** argv){
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(20, 20);
    glutInitWindowSize(1920, 1080);
    glutCreateWindow("CS155 Assignment 5");
    
    //
    // Initialize GLEW
    //
#if !defined(__APPLE__) && !defined(__linux__)
    glewInit();
    if(!GLEW_VERSION_2_0) {
        printf("Your graphics card or graphics driver does\n"
               "\tnot support OpenGL 2.0, trying ARB extensions\n");
        
        if(!GLEW_ARB_vertex_shader || !GLEW_ARB_fragment_shader) {
            printf("ARB extensions don't work either.\n");
            printf("\tYou can try updating your graphics drivers.\n"
                   "\tIf that does not work, you will have to find\n");
            printf("\ta machine with a newer graphics card.\n");
            exit(1);
        }
    }
#endif
    
    Camera camera = Camera();
    Input input = Input(&camera);
    
    SimpleShaderProgram shader = SimpleShaderProgram();
    shader.LoadVertexShader("shaders/gtb.vert");
    shader.LoadFragmentShader("shaders/gtb.frag");
    
    Tunnel tunnel = Tunnel();
    
    Scene scene = Scene(&camera, &input, &tunnel, &shader);
    scenePointer = &scene;
    inputPointer = &input;
    
    glutDisplayFunc(NoOp);
    glutReshapeFunc(ReshapeFunc);
    glutKeyboardFunc(KeyboardFunc);
    glutKeyboardUpFunc(KeyboardUpFunc);
    glutPassiveMotionFunc(MouseMotionFunc);
    FrameTimer(0);
    
    glutMainLoop();
    return 0;
}
