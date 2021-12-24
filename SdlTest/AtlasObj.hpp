//
//  AtlasObj.hpp
//  SdlTest
//
//  Created by Yonni Zohar on 24/12/2021.
//

#ifndef AtlasObj_hpp
#define AtlasObj_hpp

#include <stdio.h>
#include "Game.hpp"

class AtlasObj{
public:
    Json::Value data;
    SDL_Texture* texture;
};


#endif /* AtlasObj_hpp */
