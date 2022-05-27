//
//  Utilities.hpp
//  SdlTest
//
//  Created by Yonni Zohar on 25/12/2021.
//

#ifndef Utilities_hpp
#define Utilities_hpp

#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include "Point3d.hpp"
#include "Settings.hpp"
#include "Camera3d.hpp"

#define PI 3.14159265359

struct Point{
    float x;
    float y;
    float angle;
    float distanceFromCenter;
};


class Utilities{
public:
    
    //3d engine!!
    
    static Point3d translate(Point3d original, Point3d translation);
    static Point3d rotate(Point3d original, Point3d translation);
    static Point3d applyPerspective(Point3d original);
    static Point3d centerScreen(Point3d original);
    
    static Vector3 vec3Sub(Vector3 _a, Vector3 _b);
    static Vector3 vec3Cross(Vector3 _a, Vector3 _b);
    static float vec3Dot(Vector3 _a, Vector3 _b);
    static float vec3Length(Vector3 _a);
    static Vector3 vec3Norm(Vector3 _a);
    
    
    static float correctAngle(float _angleDeg);
    static float radToDegrees(float rads);
    static float degreesToRad(float degs);
    static float getAngle(float fromX, float fromY, float toX, float toY);
    static float getDistance(float p1X, float p1Y, float p2X, float p2Y);
    static std::string getDirection(float p1X, float p1Y, float p2X, float p2Y);
    static std::string getZeros(int num, int numZeros);
};







#endif /* Utilities_hpp */
