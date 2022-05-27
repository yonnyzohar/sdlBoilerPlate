//
//  Camera.cpp
//  SdlTest
//
//  Created by Yonni Zohar on 13/03/2022.
//
#include "Utilities.hpp"
#include "Camera3d.hpp"
#include "Keybaord.hpp"


double Camera3d::z0;
Point3d Camera3d::position;
Point3d Camera3d::rotation;

void Camera3d::init(Point3d _position, Point3d _rotation)
{
    position = _position;
    rotation = _rotation;
}

//////3d/////////////////////
void Camera3d::setz0()
{
    z0 = (Settings::stageWidth/2.0) / tan( Utilities::degreesToRad( FIELD_OF_VIEW/2.0 ) );
}

double Camera3d::getz0()
{
    return z0;
}


void Camera3d::update()
{
    double speed = 10;
    
    if (Keybaord::W) {
        position.z+=cos(rotation.y) * speed;
        position.x+=sin(rotation.y) * speed;
    }
    
    if (Keybaord::S) {
        position.z-=cos(rotation.y) * speed;
        position.x-=sin(rotation.y) * speed;
    }
    
    if (Keybaord::A) {
        rotation.y-=(speed/1000);
    }
    
    if (Keybaord::D) {
        rotation.y+=(speed/1000);
    }
}
