//
//  BattleZone.hpp
//  SdlTest
//
//  Created by Yonni Zohar on 11/03/2022.
//

#ifndef BattleZone_hpp
#define BattleZone_hpp

#include <stdio.h>

#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include "Game.hpp"
#include "Man.hpp"
#include "Utilities.hpp"
#include "Keybaord.hpp"
#include "Player.hpp"
#include "Cube.hpp"
#include "Polygon.hpp"

class BattleZone : public Game
{
public:
    //using Game::Game;
    BattleZone();
    ~BattleZone();
    void update(int dt) override;
    void draw(int dt) override;
    void onloaded() override;
    Player* player;
    Cube* cube1;
    Cube* cube2;
    
    typedef Game super;
    TexureData data;
};
#endif /* BattleZone_hpp */
