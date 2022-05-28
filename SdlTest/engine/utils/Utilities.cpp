//
//  Utilities.cpp
//  SdlTest
//
//  Created by Yonni Zohar on 25/12/2021.
//

#include "Utilities.hpp"

Vector3 Utilities::vec3Sub(Vector3 _a, Vector3 _b) {
    Vector3 res;
    res.x =_a.x - _b.x;
    res.y =_a.y - _b.y;
    res.z =_a.z - _b.z;
    return res;
}

Vector3 Utilities::vec3Norm(Vector3 _a)
{
    Vector3 _res;
    float len = Utilities::vec3Length(_a);
    float invLen = 1.0 / len;
    _res.x = _a.x * invLen;
    _res.y = _a.y * invLen;
    _res.z = _a.z * invLen;
    return _res;
}

float Utilities::vec3Length(Vector3 _a) {
    return sqrt(Utilities::vec3Dot(_a, _a));
}

float Utilities::vec3Dot(Vector3 _a, Vector3 _b) {
    return (_a.x * _b.x) + (_a.y * _b.y) + (_a.z * _b.z);
}



Vector3 Utilities::vec3Cross(Vector3 _a, Vector3 _b) {
    Vector3 _res;
    _res.x = (_a.y * _b.z) - (_a.z * _b.y);
    _res.y = (_a.z * _b.x) - (_a.x * _b.z);
    _res.z = (_a.x * _b.y) - (_a.y * _b.x);
    return _res;

}


//model to world
//takes each vertex in local model space and adds the world position to it
Point3d Utilities::translate(Point3d original, Point3d translation)
{
    Point3d res;
    res.x = original.x +translation.x;
    res.y = original.y +translation.y;
    res.z = original.z +translation.z;
    res.u = original.u;
    res.v = original.v;
    return res;
    
}

//world to camera view
//rotates each vertex in the world relative to the camera
//this is the magic!
Point3d Utilities::rotate(Point3d orig, Point3d rot)
{
    float cosX = cos(rot.x);
    float sinX = sin(rot.x);
    
    float cosY = cos(rot.y);
    float sinY = sin(rot.y);
    
    
    float cosZ = cos(rot.z);
    float sinZ = sin(rot.z);
    
    Point3d toReturn;
        // Rotation matrix: https://en.wikipedia.org/wiki/Rotation_matrix
        toReturn.x = orig.x * (cosZ * cosY) +
                     orig.y * (cosZ * sinY * sinX - sinZ * cosX) +
                     orig.z * (cosZ * sinY * cosX + sinZ * sinX);
    
        toReturn.y = orig.x * (sinZ * cosY) +
                     orig.y * (sinZ * sinY * sinX + cosZ * cosX) +
                     orig.z * (sinZ * sinY * cosX - cosZ * sinX);
    
        toReturn.z = orig.x * (-sinY) +
                     orig.y * (cosY * sinX) +
                     orig.z * (cosY * cosX);
    
        toReturn.u = orig.u;
        toReturn.v = orig.v;
        return toReturn;
    
    
    
}



//view to projection
//take all vertices in 3d space and smush them on to the 2d screen
//z is not important
Point3d Utilities::applyPerspective(Point3d original)
{
    double scale = Camera3d::z0 / (Camera3d::z0 + original.z);
    double returnX = original.x * scale;
    double returnY = original.y * scale;
    double returnZ = original.z;
    
                
    Point3d res;
    res.x = returnX;
    res.y = returnY;
    res.z = returnZ;
    res.u = original.u;
    res.v = original.v;
    return res;
}

//original rojection point is relative to top left of the screen
//we need to center it
Point3d Utilities::centerScreen(Point3d original)
{
    double returnX = original.x + (Settings::stageWidth / 2);
    double returnY = original.y + (Settings::stageHeight / 2);
    double returnZ = original.z;
    Point3d res;
    res.x = returnX;
    res.y = returnY;
    res.z = returnZ;
    res.u = original.u;
    res.v = original.v;
    return res;
}


//////////////////


float Utilities::correctAngle(float _angleDeg) {
    while (_angleDeg < 0) {
        _angleDeg += 360;
    }
    
    while (_angleDeg > 360) {
        _angleDeg -= 360;
    }
    
    return _angleDeg;
}

float Utilities::radToDegrees(float rads) {
    return rads * 180 / PI;
}

float Utilities::degreesToRad(float degs) {
    return degs * PI / 180;
}


float Utilities::getAngle(float fromX, float fromY, float toX, float toY) {
    float angle = atan2(toY - fromY, toX - fromX);
    return angle;
}

float Utilities::getDistance(float p1X, float p1Y, float p2X, float p2Y) {
    
    float dX = p1X - p2X;
    float dY = p1Y - p2Y;
    float dist = sqrt(dX * dX + dY * dY);
    return dist;
}


std::string Utilities::getDirection(float p1X, float p1Y, float p2X, float p2Y)
{
    
    
    std::string firstDir = "";
    std::string secondDir = "";
    
    //////////////////////
    int degrees = atan2(p1Y - p2Y, p1X - p2X) / PI * 180;
    
    while (degrees >= 360) {
        degrees -= 360;
    }
    while (degrees < 0) {
        degrees += 360;
    }
    
    
    degrees = ceil(degrees);
    
    if (degrees >= 66 && degrees < 112) {
        firstDir = "N";
    }
    if (degrees >= 22 && degrees < 66) {
        firstDir = "N";
        secondDir = "W";
    }
    
    if (degrees >= 0 && degrees < 22) {
        secondDir = "W";
    }
    
    if (degrees >= 337 && degrees <= 359) {
        secondDir = "W";
    }
    if (degrees >= 292 && degrees < 337) {
        firstDir = "S";
        secondDir = "W";
    }
    if (degrees >= 247 && degrees < 292) {
        firstDir = "S";
    }
    if (degrees >= 202 && degrees < 247) {
        firstDir = "S";
        secondDir = "E";
    }
    if (degrees >= 157 && degrees < 202) {
        secondDir = "E";
    }
    
    if (degrees >= 112 && degrees < 157) {
        firstDir = "N";
        secondDir = "E";
    }
    
    
    return firstDir + "" + secondDir;
}


std::string Utilities::getZeros(int num, int numZeros)
{
    std::string num_str =std::to_string(num);
    int len = num_str.length();
    std::string str = "";
    for (int i = 0; i < numZeros - len; i++) {
        str += "0";
    }

    str += num_str;
    return str;
}
