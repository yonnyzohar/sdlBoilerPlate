//
//  GameObject3d.hpp
//  SdlTest
//
//  Created by Yonni Zohar on 12/03/2022.
//

#ifndef GameObject3d_hpp
#define GameObject3d_hpp
#include <vector>
#include <stdio.h>
#include "Point3d.hpp"
#include "Polygon.hpp"
#include "Utilities.hpp"

//#include "Polygon.hpp"

class GameObject3d {
    public:
    GameObject3d(Point3d _positon, Point3d _rotation, SDL_Surface* _surface);
    ~GameObject3d();
    void draw();
    virtual void update();
    std::vector<Polygon*> polygons;
    std::vector<Point3d> vertexes;// the original verteces on the model
    std::vector<Point3d> drawPoints;//the end points after manipulation to be drawn

    Point3d position;
    Point3d rotation;
    SDL_Surface* surface;
    
    
    void collectPolygons(std::vector<Polygon*>& totalPolygons);
};

#endif /* GameObject3d_hpp */
