//
//  Point3d.hpp
//  SdlTest
//
//  Created by Yonni Zohar on 12/03/2022.
//

#ifndef Point3d_hpp
#define Point3d_hpp

#include <stdio.h>

struct Vector3{
    double x;
    double y;
    double z;
};


struct Point3d{
    double x;
    double y;
    double z;
    double u;
    double v;
    
    static Point3d create(Point3d p, double _u, double _v)
    {
        Point3d toReturn;
        toReturn.x = p.x;
        toReturn.y = p.y;
        toReturn.z = p.z;
        toReturn.u = _u;
        toReturn.v = _v;
        return toReturn;
    }
    
    static Point3d create(double _x, double _y, double _z, double _u = 0, double _v = 0)
    {
        Point3d toReturn;
        toReturn.x = _x;
        toReturn.y = _y;
        toReturn.z = _z;
        toReturn.u = _u;
        toReturn.v = _v;
        return toReturn;
    }
};

#endif /* Point3d_hpp */
