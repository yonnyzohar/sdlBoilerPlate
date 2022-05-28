//
//  Player.hpp
//  SdlTest
//
//  Created by Yonni Zohar on 11/03/2022.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include "Game.hpp"
#include "Utilities.hpp"
#include "Keybaord.hpp"



class Player
{
public:
    Player(float x, float y);
    ~Player();
    Point p0;
    Point p1;
    Point p2;
    Point position;
    void draw();
    void update();
    float rotation = 0;
    float speed = 0;
    
};

#endif /* Player_hpp */
