//
//  Player.cpp
//  SdlTest
//
//  Created by Yonni Zohar on 11/03/2022.
//

#include "Player.hpp"

Player::Player(float x, float y)
{
    position.x = x;
    position.y = y;
    float scale = 2;
    
    p0.x = -10;
    p0.y = -10;
    p0.angle = Utilities::getAngle( 0, 0, p0.x,  p0.y);
    p0.distanceFromCenter = Utilities::getDistance(0, 0, p0.x,  p0.y);
    
    p1.x = -10;
    p1.y = 10;
    p1.angle = Utilities::getAngle(  0, 0, p1.x,  p1.y);
    p1.distanceFromCenter = Utilities::getDistance( 0, 0, p1.x,  p1.y);
    
    p2.x = 20;
    p2.y = 0;
    p2.angle = Utilities::getAngle( 0, 0, p2.x,  p2.y);
    p2.distanceFromCenter = Utilities::getDistance(0, 0, p2.x,  p2.y);
    
    
    
    
}

void Player::update()
{
    speed = 0;
    
    if (Keybaord::W) {
        speed = 5;
    }
    
    if (Keybaord::S) {
        speed = -5;
    }
    
    if (Keybaord::A) {
        rotation-=5;
    }
    
    if (Keybaord::D) {
        rotation+=5;
    }
    
    //position.x ++;
    
    if (rotation > 360)
    {
        rotation = 0;
    }
    
    position.x += cosf(Utilities::degreesToRad(rotation)) * speed;
    position.y += sinf(Utilities::degreesToRad(rotation)) * speed;
}

void Player::draw(){

    SDL_SetRenderDrawColor(SDL_Utils::renderer, 255, 0, 0, 255);
    //player's current rotation in radians
    float radian = Utilities::degreesToRad(rotation);
    
    Point _p0;
    _p0.angle = p0.angle + radian;
    _p0.x = (cosf(_p0.angle) * p0.distanceFromCenter);
    _p0.y = (sinf(_p0.angle) * p0.distanceFromCenter);
    
    Point _p1;
    _p1.angle = p1.angle + radian;
    _p1.x = (cosf(_p1.angle) * p1.distanceFromCenter);
    _p1.y = (sinf(_p1.angle) * p1.distanceFromCenter);
    
    Point _p2;
    _p2.angle = p2.angle + radian;
    _p2.x = (cosf(_p2.angle) * p2.distanceFromCenter);
    _p2.y = (sinf(_p2.angle) * p2.distanceFromCenter);
    
    //line from 0 -> 1
    //float p1X, float p1Y, float p2X, float p2Y
    float line = Utilities::getDistance(  _p0.x, _p0.y,  _p1.x,  _p1.y);
    float angle = Utilities::getAngle(  _p0.x,  _p0.y,  _p1.x,  _p1.y);
    
    
    for (int i = 0; i < (int)line; i++)
    {
        int x = _p0.x + (cosf(angle) * i);
        int y = _p0.y + (sinf(angle) * i);
        
        SDL_RenderDrawPoint(SDL_Utils::renderer, x + position.x, y + position.y);
    }
    
    line = Utilities::getDistance((float) _p1.x, (float) _p1.y, (float) _p2.x, (float) _p2.y);
    angle = Utilities::getAngle( (float) _p1.x, (float) _p1.y, (float) _p2.x, (float) _p2.y);
    
    
    for (int i = 0; i < (int)line; i++)
    {
        int x = _p1.x + (cosf(angle) * i);
        int y = _p1.y + (sinf(angle) * i);
        
        SDL_RenderDrawPoint(SDL_Utils::renderer, x + position.x, y + position.y);
    }
    
    line = Utilities::getDistance((float) _p2.x, (float) _p2.y, (float) _p0.x, (float)_p0.y);
    angle = Utilities::getAngle( (float) _p2.x, (float) _p2.y, (float) _p0.x, (float) _p0.y);
    
    
    for (int i = 0; i < (int)line; i++)
    {
        int x = _p2.x + (cosf(angle) * i);
        int y = _p2.y + (sinf(angle) * i);
        
        SDL_RenderDrawPoint(SDL_Utils::renderer, x + position.x, y + position.y);
    }
}

Player::~Player()
{
    
}
