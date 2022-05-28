//
//  Cube.hpp
//  SdlTest
//
//  Created by Yonni Zohar on 12/03/2022.
//

#ifndef Cube_hpp
#define Cube_hpp

#include <stdio.h>
#include "GameObject3d.hpp"


class Cube : public GameObject3d
{
public:
    //using GameObject3d::GameObject3d;
    Cube(Point3d _positon, Point3d _rotation, double scale, SDL_Surface* _surface );
    ~Cube();
    typedef GameObject3d super;
    void update();
    
    
};

#endif /* Cube_hpp */
