//
//  Camera.hpp
//  SdlTest
//
//  Created by Yonni Zohar on 13/03/2022.
//

#ifndef Camera3d_hpp
#define Camera3d_hpp

#define FIELD_OF_VIEW 45
#import "Point3d.hpp"

#include <stdio.h>
class Camera3d{
public:
    
    static Point3d position;
    static Point3d rotation;
    static double z0;//this is the distance from palyer to screen
    static double getz0();
    static void setz0();
    static void update();
    static void init(Point3d _position, Point3d _rotation);
};

#endif /* Camera3d_hpp */
