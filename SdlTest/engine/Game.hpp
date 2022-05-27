//
//  Game.cpp
//  SdlTest
//
//  Created by Yonni Zohar on 23/12/2021.
//

#ifndef Game_hpp
#define Game_hpp


#include "SDL_Utils.hpp"
#include <stdio.h>
#include <vector>
#include <string>
#include "json.h"
#include "reader.h"
#include "value.h"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "AtlasObj.hpp"
#include "Keybaord.hpp"
#include "JsonHandler.hpp"
#include "Point3d.hpp"
#include "Settings.hpp"
#include "GameObject3d.hpp"
#include "Polygon.hpp"
#include "Utilities.hpp"
#include "Camera3d.hpp"

class Game {
    
public:
    Game();
    ~Game();
    std::vector<Polygon*> totalPolygons;
    std::vector<Polygon*> totalPolygonsPreClip;
    
    std::vector<GameObject3d*> entities3d;
    
    void init(const char* title, int xPos, int yPos, int width, int height, bool fulScreen, int r = 0, int g = 0, int b = 0);
    void handleEvents();
    virtual void update( int dt);
    void render(int dt);
    void clean();
    virtual void onloaded();
    virtual void draw(int dt);
    bool running(){return  isRunning;}
    void loadAssetFromDisk(std::string dirName);
    void parseJsonToMap(Json::Value &data, std::map<std::string,Frame> &frames, int &numZeros);
    void earlyUpdate();
    void lateUpdate();
    

    std::map<std::string, AtlasObj*> assetsMap;
    
    int r;
    int g;
    int b;
    static Frame Camera;
    

protected:
    bool isRunning;
    

};
#endif
