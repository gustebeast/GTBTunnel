//
//  util.h
//  CS155 Project
//
//  Created by Gus Callaway on 10/29/17.
//  Copyright © 2017 Gus Callaway. All rights reserved.
//

#ifndef util_h
#define util_h

#include <cmath>
#include <cstdio>

struct Vec3f {
    float x, y, z;
    
    Vec3f() { }
    Vec3f(float _x, float _y, float _z) : x(_x), y(_y), z(_z) { }
    Vec3f(float* xyz) : x(xyz[0]), y(xyz[1]), z(xyz[2]) { }

    Vec3f operator*(float s) { return Vec3f(x*s, y*s, z*s); }
    Vec3f operator/(float s) { return Vec3f(x/s, y/s, z/s); }
    Vec3f operator-() { return Vec3f(-x, -y, -z); }
    Vec3f operator+(const Vec3f& o) { return Vec3f(x+o.x, y+o.y, z+o.y); }
    Vec3f operator-(const Vec3f& o) { return Vec3f(x-o.x, y-o.y, z-o.z); }
    void operator+=(const Vec3f& o) { x+=o.x;y+=o.y;z+=o.z; }
    void operator-=(const Vec3f& o) { x-=o.x;y-=o.y;z-=o.z; }
    void operator*=(const Vec3f& o) { x*=o.x;y*=o.y;z*=o.z; }
    
    float* data() {
        return &x;
    }
    void print() {
        printf("(%f, %f, %f)\n", x, y, z);
    }
    Vec3f crossProduct(const Vec3f &o) {
        return Vec3f(
                     y * o.z - z * o.y,
                     z * o.x - x * o.z,
                     x * o.y - y * o.x
                     );
    }
    float magnitude() {
        return sqrtf(x*x + y*y + z*z);
    }
    
    Vec3f rotate(float angle, float y_ = -1) {
        if (y_ == -1) { y_ = y; }
        return Vec3f(x*cos(angle) - z*sin(angle), y_, x*sin(angle) + z*cos(angle));
    }
};

struct Vec2f {
    float x, y;
    
    Vec2f() { }
    Vec2f(float _x, float _y) : x(_x), y(_y) { }
    Vec2f(float* xy) : x(xy[0]), y(xy[1]) { }
    
    float* data() {
        return &x;
    }
    void print() {
        printf("(%f, %f)\n", x, y);
    }
};

struct Tri {
    unsigned int positionIndices[3];
    unsigned int texCoordIndices[3];
    unsigned int normalIndices[3];
};

#endif /* util_h */
