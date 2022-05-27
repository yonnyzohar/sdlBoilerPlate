//
//  Polygon.hpp
//  SdlTest
//
//  Created by Yonni Zohar on 12/03/2022.
//

#ifndef Polygon_hpp
#define Polygon_hpp

#include "SDL_Utils.hpp"
#include <stdio.h>
#include <string>
#include <vector>
#include <list>
#include <stdio.h>
#include "Point3d.hpp"
#include "Utilities.hpp"
#include "Camera3d.hpp"
#include "TextureUtils.hpp"

class Polygon{
public:
    Polygon(Point3d p0, Point3d p1, Point3d p2, SDL_Surface* _surface);
    ~Polygon();
    Point3d localPositions[3];
    Point3d worldPositions[3] ;
    Point3d cameraPositions[3];
    Point3d screenPositions[3];
    /*
    Point3d p1;
    Point3d p2;
    Point3d p3;
     */
    //get the average z of the polygon and sort all polygons be average z distance.
    //that way you can draw the far away ones first
    double averageZ;
    
    //the normal z is used to determine if the polygn is facing us of not.
    //if the vertices are going clockwise the normal z will be negative-> facing us.
    //if the verties are counter clockwise, normal z is positive, hence facing away from us
    double normalZ;
    
    Point3d getWorldTranslation(Point3d p, Point3d _rotation, Point3d _position);
    Point3d getScreenTranslation(Point3d p);
    void calculateScreenPos();
    void calculateCameraView();
    void calculateWorldPos(Point3d _rotation, Point3d _position);
    void draw();
    std::list<Polygon*> getZClippedTriangles();
    //void fillSDL();
    void fillTriangle();
    void outline();
    void sortPoints();
    static bool sortZ(Polygon* p1, Polygon* p2);
    SDL_Surface* surface;
    
    
    
    
};

#endif /* Polygon_hpp */
