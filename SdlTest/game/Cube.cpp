//
//  Cube.cpp
//  SdlTest
//
//  Created by Yonni Zohar on 12/03/2022.
//

#include "Cube.hpp"
//
Cube::Cube(Point3d _positon,  Point3d _rotation, double scale, SDL_Surface* _surface):GameObject3d( _positon, _rotation, _surface)
{

    /*
    vertexes.push_back(Point3d::create(-100, -100, -100)); //0: left top front
    vertexes.push_back(Point3d::create(-100, 100, -100));  //1: left bttom front
    vertexes.push_back(Point3d::create(100, 100, -100));   //2: right bottom front
    vertexes.push_back(Point3d::create(100, -100, -100));  //3: right top front
    vertexes.push_back(Point3d::create(-100, -100, 100));  //4: left top back
    vertexes.push_back(Point3d::create(-100, 100, 100));   //5: left bottom back
    vertexes.push_back(Point3d::create(100, 100, 100));    //6: right bottom back
    vertexes.push_back(Point3d::create(100, -100, 100));   //7: right top back
    */
    
    double size = 100 * scale;
    
    //now create the polygons
    //front surface
    Polygon* p = new Polygon(Point3d::create(-size, -size, -size, 0, 0),Point3d::create(-size,  size, -size, 0, 1),Point3d::create( size, -size, -size, 1, 0), surface );
    polygons.push_back(p);//013
    
    p = new Polygon(Point3d::create(-size,  size, -size, 0, 1),
                    Point3d::create( size,  size, -size, 1, 1),
                    Point3d::create( size, -size, -size, 1, 0), surface);
    
    polygons.push_back(p);//123
    ///////////////////////////////////////////////////////////////
    
    //back surface
    p = new Polygon(Point3d::create( size, -size , size, 1, 0),
                    Point3d::create(-size,  size , size, 0, 1),
                    Point3d::create(-size, -size , size, 0, 0), surface);
    
    polygons.push_back(p);//754
    
    p = new Polygon(Point3d::create( size, -size, size, 1, 0),
                    Point3d::create( size,  size, size, 1, 1),
                    Point3d::create(-size,  size, size, 0, 1),surface);
    
    polygons.push_back(p);//765
    ///////////////////////////////////////////////////////////////
    
    //bottom surface
    p = new Polygon(Point3d::create(-size, -size,  size, 0, 1),
                    Point3d::create(-size, -size, -size, 0, 0),
                    Point3d::create( size, -size,  size, 1, 1),surface);
    
    polygons.push_back(p);//407
    
    p = new Polygon(Point3d::create(-size, -size, -size, 0, 0),
                    Point3d::create( size, -size, -size, 1, 0),
                    Point3d::create( size, -size,  size, 1, 1),surface);
    
    polygons.push_back(p);//037
    ///////////////////////////////////////////////////////////////
    
    //top surface
    p = new Polygon(Point3d::create(-size, size, -size, 0, 0),
                    Point3d::create( size, size,  size, 1, 1),
                    Point3d::create( size, size, -size, 1, 0),surface);
    
    polygons.push_back(p);//162
    
    p = new Polygon(Point3d::create(-size, size, -size, 0, 0),
                    Point3d::create(-size, size,  size, 0, 1),
                    Point3d::create( size, size,  size, 1, 1),surface);
    
    polygons.push_back(p);//156
    ///////////////////////////////////////////////////////////////
    
    //left surface
    p = new Polygon(Point3d::create(-size, -size,  size, 0, 1),
                    Point3d::create(-size,  size, -size, 1, 0),
                    Point3d::create(-size, -size, -size, 0, 0),surface);
    
    polygons.push_back(p);//410
    
    p = new Polygon(Point3d::create(-size, -size,  size, 0, 1),
                    Point3d::create(-size,  size,  size, 1, 1),
                    Point3d::create(-size,  size, -size, 1, 0),surface);
    
    polygons.push_back(p);//451
    ///////////////////////////////////////////////////////////////
    
    //right surface
    p = new Polygon(Point3d::create(size, -size, -size, 0, 0),
                    Point3d::create(size,  size, -size, 1, 0),
                    Point3d::create(size, -size,  size, 0, 1),surface);
    
    polygons.push_back(p);//327
    
    
    p = new Polygon(Point3d::create(size, -size,  size, 0, 1),
                    Point3d::create(size,  size, -size, 1, 0),
                    Point3d::create(size,  size,  size, 1, 1),surface);
    
    polygons.push_back(p); //726
    ///////////////////////////////////////////////////////////////
    
    
    //super::setModel();
    
    
    //the makeup of the polygons is important. they need to be clockwise!

}

void Cube::update() {
    rotation.y += 0.1;
    rotation.x += 0.1;
    rotation.z += 0.1;
    super::update();
}
/* */
