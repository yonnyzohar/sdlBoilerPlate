//
//  SDL_Utils.hpp
//  SdlTest
//
//  Created by Yonni Zohar on 27/05/2022.
//

#ifndef SDL_Utils_hpp
#define SDL_Utils_hpp
#include <SDL2_image/SDL_image.h>
#include <SDL2/SDL.h>
#include <stdio.h>

class SDL_Utils {
    
public:
    static SDL_Event event;
    static SDL_Window *window;
    static SDL_Rect *cam;
    static SDL_Renderer *renderer;
    static SDL_Surface* gScreenSurface ;
};

#endif /* SDL_Utils_hpp */
