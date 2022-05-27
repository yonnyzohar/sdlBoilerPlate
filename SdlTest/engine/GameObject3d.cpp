//
//  GameObject3d.cpp
//  SdlTest
//
//  Created by Yonni Zohar on 12/03/2022.
//

#include "GameObject3d.hpp"

GameObject3d::GameObject3d(Point3d _positon, Point3d _rotation, SDL_Surface* _surface)
{
    // constructor code
    position = _positon;//
    rotation = _rotation;//;
    surface = _surface;
}

void GameObject3d::update()
{
    
}

void GameObject3d::draw(){
    /*
    SDL_SetRenderDrawColor(Utilities::renderer, 255, 0, 0, 255);
    int len = drawPoints.size();
    for(int i = 0; i < len-1; i++)
    {
    
       Point3d *dp0 = &drawPoints[i];
       Point3d *dp1 = &drawPoints[i+1];
        
         
        
        float line = Utilities::getDistance(  dp0->x, dp0->y,  dp1->x,  dp1->y);
        float angle = Utilities::getAngle(  dp0->x,  dp0->y,  dp1->x,  dp1->y);
        
        for (int j = 0; j < (int)line; j++)
        {
            int x = dp0->x + (cosf(angle) * j);
            int y = dp0->y + (sinf(angle) * j);
            
            SDL_RenderDrawPoint(Utilities::renderer, x , y);
        }
        
    }
     */
    
    
}


GameObject3d::~GameObject3d()
{
    
}


