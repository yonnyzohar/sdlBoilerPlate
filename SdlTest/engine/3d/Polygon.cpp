//
//  Polygon.cpp
//  SdlTest
//
//  Created by Yonni Zohar on 12/03/2022.
//

/*
 

 
 */

#include "Polygon.hpp"

Polygon::Polygon(Point3d p0, Point3d p1, Point3d p2, SDL_Surface* _surface){
    localPositions[0] = p0;
    localPositions[1] = p1;
    localPositions[2] = p2;
    cameraPositions[0] = p0;
    cameraPositions[1] = p1;
    cameraPositions[2] = p2;
    screenPositions[0] = p0;
    screenPositions[1] = p1;
    screenPositions[2] = p2;
    surface = _surface;
}

void Polygon::calculateWorldPos(Point3d _rotation, Point3d _position)
{
    worldPositions[0] = getWorldTranslation(localPositions[0], _rotation, _position);
    worldPositions[1] = getWorldTranslation(localPositions[1], _rotation, _position);
    worldPositions[2] = getWorldTranslation(localPositions[2], _rotation, _position);
   
}


Point3d Polygon::getWorldTranslation(Point3d p, Point3d _rotation, Point3d _position)
{
    //rotation
    Point3d p1 = Utilities::rotate(p, _rotation);
    // translate
    Point3d p2 = Utilities::translate(p1, _position);
    return p2;
}
   
void Polygon::calculateCameraView()
{

    int i = 0;

    // Translate
    Point3d translateBy = Point3d::create(Camera3d::position.x * -1.0, Camera3d::position.y * -1.0, Camera3d::position.z * -1.0);
    for (i = 0; i < 3; i++) {
        cameraPositions[i] = Utilities::translate(worldPositions[i], translateBy);
    }

    // Rotate
    Point3d rotateBy = Point3d::create(Camera3d::rotation.x * -1.0, Camera3d::rotation.y * -1.0, Camera3d::rotation.z * -1.0);
    for (i = 0; i < 3; i++) {
        Point3d camPos = Point3d::create(cameraPositions[i].x, cameraPositions[i].y, cameraPositions[i].z, cameraPositions[i].u, cameraPositions[i].v);

        cameraPositions[i] = Utilities::rotate(camPos, rotateBy);
        cameraPositions[i].u = camPos.u;
        cameraPositions[i].v = camPos.v;
    }
 
    /**/
    // Average Z (for sorting triangles)
    averageZ = (cameraPositions[0].z + cameraPositions[1].z + cameraPositions[2].z) / 3.0;
}

bool Polygon::sortZ(Polygon* p1, Polygon* p2)
{
    return p1->averageZ > p2->averageZ;
}
    

void Polygon::calculateScreenPos()
{
    screenPositions[0] = getScreenTranslation(cameraPositions[0]);
    screenPositions[1] = getScreenTranslation(cameraPositions[1]);
    screenPositions[2] = getScreenTranslation(cameraPositions[2]);
    
    double sp0X = screenPositions[0].x;
    double sp0Y = screenPositions[0].y;
    double sp0Z = screenPositions[0].z;
    
    double sp1X = screenPositions[1].x;
    double sp1Y = screenPositions[1].y;
    double sp1Z = screenPositions[1].z;
    
    double sp2X = screenPositions[2].x;
    double sp2Y = screenPositions[2].y;
    double sp2Z = screenPositions[2].z;
    
    
    //get cross product of polygon
    Vector3 a;
    a.x = sp1X - sp0X;
    a.y = sp1Y - sp0Y;
    a.z = sp1Z - sp0Z;
                    

    Vector3 b;
    b.x = sp2X - sp0X;
    b.y = sp2Y - sp0Y;
    b.z = sp2Z - sp0Z;
    
    Vector3 cross = Utilities::vec3Cross(a, b);
    normalZ = cross.z;

    //normal z - is the triangle facing us or the other way
    /*
    normalZ = (sp1X - sp0X) *
              (sp2Y - sp0Y) - (sp1Y - sp0Y) *
              (sp2X - sp0X);
     */
}


Point3d Polygon::getScreenTranslation(Point3d p)
{
    //perspective
    p = Utilities::applyPerspective(p);
    //center on screen
    p = Utilities::centerScreen(p);

    return p;
}

/*
void Polygon::fillSDL(){
    
    SDL_SetRenderDrawColor(Utilities::renderer, 255, 0, 0, 255);
    
    SDL_Vertex vert[3];
    
    for(int i = 0; i < 3; i++)
    {
        Point3d dp = screenPositions[i];
        
        vert[i].position.x  = dp.x;
        vert[i].position.y  = dp.y;
        vert[i].tex_coord.x = dp.u;
        vert[i].tex_coord.y = dp.v;
        
        vert[i].color.r = 255;
        vert[i].color.g = 255;
        vert[i].color.b = 255;
        vert[i].color.a = 255;
        
       
       
        
    }
    SDL_RenderGeometry(Utilities::renderer, texture, vert, 3, NULL, 0);
}
 */
//screen positions vector contains x and y in screen space and z in camera space
        //so we can use a z buffer
//zBuffer: Array
void Polygon::fillTriangle()
{
    //must sort the points from top to bottom for line by line rasterising to work
    sortPoints();
    
    
   SDL_PixelFormat *fmt = surface->format;
   Point3d p0 = screenPositions[0];
   Point3d p1 = screenPositions[1];
   Point3d p2 = screenPositions[2];
    
   float texW = surface->w;
   float texH = surface->h;

   float p0x = p0.x;
   float p0y = p0.y;
   float p0u = p0.u;
   float p0v = p0.v;
   //float p0w = p0.w;
   float p0z = p0.z;

   float p1x = p1.x;
   float p1y = p1.y;
   float p1u = p1.u;
   float p1v = p1.v;
   //float p1w = p1.w;
   float p1z = p1.z;

   float p2x = p2.x;
   float p2y = p2.y;
   float p2u = p2.u;
   float p2v = p2.v;
   //float p2w = p2.w;
   float p2z = p2.z;


     //each triangle is split in 2 to make calculations easier.
     //first we do the top part, then the bottom part
     if (p0y < p1y) {
         
         float side1Width =(p1x - p0x);
         float side1Height = (p1y - p0y);
         //slope from top to first side - by how much does x progress when y progresses by 1!
         float slope1 = side1Width / side1Height;
         
         float side2Width = (p2x - p0x);
         float side2Height = (p2y - p0y);

         //slope from top to second side - by how much does x progress when y progresses by 1!
         float slope2 = side2Width / side2Height;
         
         for (int i = 0; i <= side1Height; i++) {
             int _y = p0y + i; // when y grows by 1
             int startX = p0x + i * slope1;// start x grows by initial x + (i * slope1)
             int endX = p0x + i * slope2;// end x grows by initial x + (i * slope2)
             
             float yDelta = (_y - p0y); // same as i, just float
             float side1Per = yDelta / side1Height;
             float side2Per = yDelta / side2Height;

             //u start and v start
             float us  = p0u + side1Per * (p1u - p0u);
             float ue = p0u + side2Per * (p2u - p0u);
             
             //float ws  = p0w + side1Per * (p1w - p0w);
             //float we = p0w + side2Per * (p2w - p0w);

             //u end and v end
             float vs = p0v + side1Per * (p1v - p0v);
             float ve = p0v + side2Per * (p2v - p0v);

             //z buffer start and end
             float zs = p0z + side1Per * (p1z - p0z);
             float ze = p0z + side2Per * (p2z - p0z);

             //if start is greater than and, swap the,
             if (startX > endX) {
                 float aux = startX;
                 startX = endX;
                 endX = aux;

                 //and also swap uv
                 aux = us;
                 us = ue;
                 ue = aux;
                 aux = vs;
                 vs = ve;
                 ve = aux;

                 //swap w
                 //aux = ws;
                // ws = we;
                // we = aux;

                 //swap z
                 aux = zs;
                 zs = ze;
                 ze = aux;

             }

             if (endX > startX) {
                 float triangleCurrWidth = endX - startX;
                 
                 //this is the initial u which we will increment
                 float u = us * texW;
                 //this is the increment step on the u axis
                 float ustep = (ue - us) / triangleCurrWidth * texW;
                 //this is the initial v which we will increment
                 float v = vs * texH;
                 //this is the increment step on the v axis
                 float vstep = (ve - vs) / triangleCurrWidth * texH;
                 //float w = ws;
                // float wstep = (we - ws) / triangleCurrWidth;
                 float z = zs;
                 float zstep = (ze - zs) / (triangleCurrWidth);


                 for (int j = 0; j <= triangleCurrWidth; j++) {
                     int _x  = startX + j;
                     u += ustep;
                     v += vstep;
                     //w += wstep;
                     z += zstep;

                    // if (zBuffer[Engine.resolutionX * _y + _x] == 0 || zBuffer[Engine.resolutionX * _y + _x] > z) {
                    
                     Uint32 pixel = TextureUtils::getPixel( surface, u , v );//u / w, v / w
                     SDL_Color rgb;
                     SDL_GetRGB(pixel, surface->format, &rgb.r, &rgb.g, &rgb.b);
                     TextureUtils::setPixel(SDL_Utils::gScreenSurface, _x, _y, rgb.r, rgb.g, rgb.b);
                     
                     //SDL_SetRenderDrawColor(SDL_Utils::renderer, rgb.r, rgb.g, rgb.b, 255);
                     //SDL_RenderDrawPoint(SDL_Utils::renderer, _x, _y);
                     /**/
                     
                         //var pixel: uint = bd.getPixel(u / w, v / w);
                         //Engine.bd.setPixel(_x, _y, pixel);
                         //zBuffer[Engine.resolutionX * _y + _x] = z;
                    // }

                 }
             }
         }
     }

     ////
     //bottom part of the triangle
     if (p1y < p2y) {
         
         float side3Width = (p2x - p1x);
         float side3Height = (p2y - p1y);
         //slope from top to first side  - by how much does x progress when y progresses by 1!
         float slope3 = side3Width / side3Height;
         
         float side2Width = (p2x - p0x);
         float side2Height = (p2y - p0y);
         //slope from top to second side  - by how much does x progress when y progresses by 1!
         float slope2 = side2Width / side2Height;
         
         //this is the middle point on slope 2
         //the slope means - when we move y by 1, how much does x move by?
         //so if we start at the bottom and decrease the side3Height * the slope of side 2 we will get the start point
         //THIS IS MAGIC!!!!
         float midPointXSlope2 = p2x - (side3Height * slope2);
         

         for (int i = 0; i <= side3Height; i++) {
             int startX = p1x + i * slope3;
             int endX = midPointXSlope2 + i * slope2;
             int _y = p1y + i;
             float yDelta = (_y - p1y); // same as i, just float

             //u start and v start
             float side3Per = (yDelta / side3Height);
             float us = p1u + side3Per * (p2u - p1u);
             float vs = p1v + side3Per * (p2v - p1v);

             //float ws = p1w + side3Per * (p2w - p1w);

             //u nd and v end
             float side2Per = (_y - p0y) / side2Height;
             float ue = p0u + side2Per * (p2u - p0u);
             float ve = p0v + side2Per * (p2v - p0v);

             //float we = p0w + side2Per * (p2w - p0w);

             //z buffer start and end
             float zs = p1z + side3Per * (p2z - p1z);
             float ze = p0z + side2Per * (p2z - p0z);

             if (startX > endX) {
                 float aux = startX;
                 startX = endX;
                 endX = aux;

                 //and also swap uv
                 aux = us;
                 us = ue;
                 ue = aux;
                 aux = vs;
                 vs = ve;
                 ve = aux;

                 //swap w
                // aux = ws;
                // ws = we;
                // we = aux;

                 //swap z
                 aux = zs;
                 zs = ze;
                 ze = aux;
             }

             if (endX > startX) {
                 float triangleCurrWidth = endX - startX;

                 float u = us * texW;
                 float ustep = (ue - us) / triangleCurrWidth * texW;
                 float v = vs * texH;
                 float vstep = (ve - vs) / triangleCurrWidth * texH;

                 //float w = ws;
                 //float wstep = (we - ws) / triangleCurrWidth;

                 float z = zs;
                 float zstep = (ze - zs) / (triangleCurrWidth);

                 for (int j  = 0; j <= triangleCurrWidth; j++) {
                     int _x = j + startX;
                     u += ustep;
                     v += vstep;
                     //w += wstep;
                     z += zstep;

                     //if (zBuffer[Engine.resolutionX * _y + _x] == 0 || zBuffer[Engine.resolutionX * _y + _x] > z) {
                         
                         Uint32 pixel = TextureUtils::getPixel( surface, u , v );//u / w, v / w
                         SDL_Color rgb;
                         SDL_GetRGB(pixel, surface->format, &rgb.r, &rgb.g, &rgb.b);
                         TextureUtils::setPixel(SDL_Utils::gScreenSurface, _x, _y, rgb.r, rgb.g, rgb.b);
                         
                         //SDL_SetRenderDrawColor(SDL_Utils::renderer, rgb.r, rgb.g, rgb.b, 255);
                        // SDL_RenderDrawPoint(SDL_Utils::renderer, _x, _y);
                     /* */
                     /*
                         var pixel: uint = bd.(u / w, v / w);
                         Engine.bd.setPixel(_x, _y, pixel);
                         zBuffer[Engine.resolutionX * _y + _x] = z;
                      */
                     //}

                 }
             }
         }

     }
}

void Polygon::sortPoints()
{
     Point3d aux;
     //if point 0 is lower than point 1, then point 1 needs to be 0
     if (screenPositions[0].y > screenPositions[1].y) {
         aux = screenPositions[0];
         screenPositions[0] = screenPositions[1];
         screenPositions[1] = aux;
     }
     //if point 0 is lower than point 2, then point 2 needs to be 0
     if (screenPositions[0].y > screenPositions[2].y) {
         aux = screenPositions[0];
         screenPositions[0] = screenPositions[2];
         screenPositions[2] = aux;
     }
     //if point 1 is lower than point 2, then point 2 needs to be 1
     if (screenPositions[1].y > screenPositions[2].y) {
         aux = screenPositions[1];
         screenPositions[1] = screenPositions[2];
         screenPositions[2] = aux;
     }
 }



void Polygon::outline(){
    //SDL_SetRenderDrawColor(SDL_Utils::renderer, 255, 255, 255, 255);
    //SDL_RenderClear(renderer);
    
    for(int i = 0; i < 3; i++)
    {
        Point3d dp0 = screenPositions[i];
        Point3d dp1 = screenPositions[i+1];
         if (i == 2)
         {
             dp1 = screenPositions[0];
         }
         
         float line = Utilities::getDistance(  dp0.x, dp0.y,  dp1.x,  dp1.y);
         float angle = Utilities::getAngle(  dp0.x,  dp0.y,  dp1.x,  dp1.y);
         
         for (int j = 0; j < (int)line; j++)
         {
             int x = dp0.x + (cosf(angle) * j);
             int y = dp0.y + (sinf(angle) * j);
             TextureUtils::setPixel(SDL_Utils::gScreenSurface , x, y, 100,100,100);
            // SDL_RenderDrawPoint(SDL_Utils::renderer, x , y);
         }
    }
    
            
    //SDL_RenderPresent(Utilities::renderer);
}

void Polygon::draw(){
    
   // fillSDL();
    
    fillTriangle();
    outline();
    
    
}

//checks if triangles are partially inside the frusom or if they are behind me.
//in that case we need to clip them (dont need to render what is behind me)
std::list<Polygon*> Polygon::getZClippedTriangles()
{
    std::list<Polygon*> toReturn;
    toReturn.push_back(new Polygon(cameraPositions[0], cameraPositions[1], cameraPositions[2], surface));

    int noTriangles;
    std::vector<Point3d> insidePoints;
    std::vector<Point3d> outsidePoints;

    // Z
    noTriangles = toReturn.size();
    for (int i = 0; i < noTriangles; i++) {

        Polygon* currentTriangle = toReturn.front();
        toReturn.pop_front();

        insidePoints.clear();
        outsidePoints.clear();

        bool pointsAreOutside[3];
        for (int i = 0; i < 3; i++)
        {
            pointsAreOutside[i] = currentTriangle->cameraPositions[i].z < -Camera3d::getz0();//
            if (pointsAreOutside[i])
            {
                outsidePoints.push_back(currentTriangle->cameraPositions[i]);
            }
            else
            {
                insidePoints.push_back(currentTriangle->cameraPositions[i]);
            }
                
        }
        delete currentTriangle;
        if (outsidePoints.size() == 0)
        {
            toReturn.push_back(new Polygon(insidePoints[0], insidePoints[1], insidePoints[2], surface));
        }
        else if (outsidePoints.size() == 1)
        {
            Point3d extraPoint1;
            extraPoint1.x = outsidePoints[0].x + (0 - outsidePoints[0].z) * (insidePoints[0].x - outsidePoints[0].x) / (insidePoints[0].z - outsidePoints[0].z);
            extraPoint1.y = outsidePoints[0].y + (0 - outsidePoints[0].z) * (insidePoints[0].y - outsidePoints[0].y) / (insidePoints[0].z - outsidePoints[0].z);
            extraPoint1.z = 0;
            extraPoint1.u = outsidePoints[0].u + (0 - outsidePoints[0].z) * (insidePoints[0].u - outsidePoints[0].u) / (insidePoints[0].z - outsidePoints[0].z);
            extraPoint1.v = outsidePoints[0].v + (0 - outsidePoints[0].z) * (insidePoints[0].v - outsidePoints[0].v) / (insidePoints[0].z - outsidePoints[0].z);
            //extraPoint1.w = outsidePoints[0].w + (0 - outsidePoints[0].z) * (insidePoints[0].w - outsidePoints[0].w) / (insidePoints[0].z - outsidePoints[0].z);

            Point3d extraPoint2;
            extraPoint2.x = outsidePoints[0].x + (0 - outsidePoints[0].z) * (insidePoints[1].x - outsidePoints[0].x) / (insidePoints[1].z - outsidePoints[0].z);
            extraPoint2.y = outsidePoints[0].y + (0 - outsidePoints[0].z) * (insidePoints[1].y - outsidePoints[0].y) / (insidePoints[1].z - outsidePoints[0].z);
            extraPoint2.z = 0;
            extraPoint2.u = outsidePoints[0].u + (0 - outsidePoints[0].z) * (insidePoints[1].u - outsidePoints[0].u) / (insidePoints[1].z - outsidePoints[0].z);
            extraPoint2.v = outsidePoints[0].v + (0 - outsidePoints[0].z) * (insidePoints[1].v - outsidePoints[0].v) / (insidePoints[1].z - outsidePoints[0].z);
            //extraPoint2.w = outsidePoints[0].w + (0 - outsidePoints[0].z) * (insidePoints[1].w - outsidePoints[0].w) / (insidePoints[1].z - outsidePoints[0].z);

            if (pointsAreOutside[0]) {
                toReturn.push_back(new Polygon(extraPoint1, insidePoints[0], insidePoints[1], surface));
                toReturn.push_back(new Polygon(extraPoint2, extraPoint1, insidePoints[1], surface));
            } else if (pointsAreOutside[1]) {
                toReturn.push_back(new Polygon(extraPoint1, insidePoints[1], insidePoints[0], surface));
                toReturn.push_back(new Polygon(extraPoint2, extraPoint1, insidePoints[0], surface));
            } else if (pointsAreOutside[2]) {
                toReturn.push_back(new Polygon(extraPoint1, insidePoints[0], insidePoints[1], surface));
                toReturn.push_back(new Polygon(extraPoint2, extraPoint1, insidePoints[1], surface));
            }
        }
        else if (outsidePoints.size() == 2)
        {
            Point3d extraPoint1;
            extraPoint1.x = outsidePoints[0].x + (0 - outsidePoints[0].z) * (insidePoints[0].x - outsidePoints[0].x) / (insidePoints[0].z - outsidePoints[0].z);
            extraPoint1.y = outsidePoints[0].y + (0 - outsidePoints[0].z) * (insidePoints[0].y - outsidePoints[0].y) / (insidePoints[0].z - outsidePoints[0].z);
            extraPoint1.z = 0;
            extraPoint1.u = outsidePoints[0].u + (0 - outsidePoints[0].z) * (insidePoints[0].u - outsidePoints[0].u) / (insidePoints[0].z - outsidePoints[0].z);
            extraPoint1.v = outsidePoints[0].v + (0 - outsidePoints[0].z) * (insidePoints[0].v - outsidePoints[0].v) / (insidePoints[0].z - outsidePoints[0].z);
           // extraPoint1.w = outsidePoints[0].w + (0 - outsidePoints[0].z) * (insidePoints[0].w - outsidePoints[0].w) / (insidePoints[0].z - outsidePoints[0].z);

            Point3d extraPoint2;
            extraPoint2.x = outsidePoints[1].x + (0 - outsidePoints[1].z) * (insidePoints[0].x - outsidePoints[1].x) / (insidePoints[0].z - outsidePoints[1].z);
            extraPoint2.y = outsidePoints[1].y + (0 - outsidePoints[1].z) * (insidePoints[0].y - outsidePoints[1].y) / (insidePoints[0].z - outsidePoints[1].z);
            extraPoint2.z = 0;
            extraPoint2.u = outsidePoints[1].u + (0 - outsidePoints[1].z) * (insidePoints[0].u - outsidePoints[1].u) / (insidePoints[0].z - outsidePoints[1].z);
            extraPoint2.v = outsidePoints[1].v + (0 - outsidePoints[1].z) * (insidePoints[0].v - outsidePoints[1].v) / (insidePoints[0].z - outsidePoints[1].z);
           // extraPoint2.w = outsidePoints[1].w + (0 - outsidePoints[1].z) * (insidePoints[0].w - outsidePoints[1].w) / (insidePoints[0].z - outsidePoints[1].z);

            if (!pointsAreOutside[0]) {
                toReturn.push_back(new Polygon(extraPoint2, insidePoints[0], extraPoint1, surface));
            } else if (!pointsAreOutside[1]) {
                toReturn.push_back(new Polygon(extraPoint1, insidePoints[0], extraPoint2, surface));
            } else if (!pointsAreOutside[2]) {
                toReturn.push_back(new Polygon(extraPoint2, insidePoints[0], extraPoint1, surface));
            }
            
        }
    }

    return toReturn;
}

Polygon::~Polygon(){
    
}

