//
//  MyGame.hpp
//  SdlTest
//
//  Created by Yonni Zohar on 24/12/2021.
//

#ifndef MyGame_hpp
#define MyGame_hpp

#include <stdio.h>
#include "Game.hpp"




class MyGame : public Game
{
public:
    void update() override;
    void draw() override;
    void onloaded() override;
    GameObject* player;
      
private:
};

#endif /* MyGame_hpp */
