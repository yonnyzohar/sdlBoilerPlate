//
//  AtlasObj.hpp
//  SdlTest
//
//  Created by Yonni Zohar on 24/12/2021.
//

#ifndef AtlasObj_hpp
#define AtlasObj_hpp

#include <stdio.h>
#include "SDL_Utils.hpp"
#include "JsonHandler.hpp"

struct Frame{
    int x;
    int y;
    int w;
    int h;
    int destW;
    int destH;
};

class AtlasObj{
public:
    Json::Value data;
    SDL_Texture* texture;
    int numZeros;
    std::map<std::string,Frame> frames;
};


#endif /* AtlasObj_hpp */
