//
//  MyGame.cpp
//  SdlTest
//
//  Created by Yonni Zohar on 24/12/2021.
//

#include "MyGame.hpp"
#include "JsonHandler.hpp"




void MyGame::onloaded()
{
    
    AtlasObj *o = new AtlasObj();
    const char* jsonPath = "/Users/yonnizohar/Desktop/c++ projects/SdlTest/SdlTest/assets/man/data.json";
    JsonHandler::loadJson(jsonPath, &o->data);

   const char* imgPath = "/Users/yonnizohar/Desktop/c++ projects/SdlTest/SdlTest/assets/man/asset.png";
    
    o->texture = TextureManager::getTexture(imgPath);
    m["man"] = *o;
    
    //std::cout << "this is my json " <<  << std::endl;
    
    player = new Man(o, 0,0, 50, 50);
    player2 = new Man(o, 0,50, 50, 50);
}


void MyGame::update()
{
    player->update();
    player2->update();
}

void MyGame::draw()
{
    player->render();
    player2->render();
}
