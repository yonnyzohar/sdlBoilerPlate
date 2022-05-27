#include "Game.hpp"


SDL_Renderer *SDL_Utils::renderer = nullptr;
SDL_Window *SDL_Utils::window = nullptr;
SDL_Rect *SDL_Utils::cam = nullptr;
SDL_Event SDL_Utils::event;
SDL_Surface * SDL_Utils::gScreenSurface = nullptr;
Frame Game::Camera;

bool useGPU = false;

Game::Game()
{
    
}

Game::~Game()
{
    
}


void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fulScreen, int _r, int _g, int _b)
{
    Settings::stageWidth = width;
    Settings::stageHeight = height;
    
    Camera3d::setz0();
    
    
    Game::Camera.x = 0;
    Game::Camera.y = 0;
    Game::Camera.w =width;
    Game::Camera.h =height;
    r = _r;
    g = _g;
    b = _b;
    
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        uint flags = SDL_WINDOW_SHOWN;
        if(fulScreen)
        {
            flags = SDL_WINDOW_FULLSCREEN;
        }
        SDL_Utils::window  = SDL_CreateWindow(title,
                                   xPos,
                                   yPos,
                                   width, height, flags);
        
        if(SDL_Utils::window)
        {
            if(useGPU)
            {
                SDL_Utils::renderer = SDL_CreateRenderer(SDL_Utils::window, -1, 0);
                if(SDL_Utils::renderer)
                {
                    SDL_SetRenderDrawColor(SDL_Utils::renderer, r, g, b, 255);

                    isRunning = true;
                    //this is where we know that sdl window is ready
                    onloaded();
                   
                }
            }
            else
            {
                SDL_Utils::gScreenSurface = SDL_GetWindowSurface( SDL_Utils::window );
                //SDL_UpdateWindowSurface(SDL_Utils::window);
                
                if(SDL_Utils::gScreenSurface)
                {
                    isRunning = true;
                    //this is where we know that sdl window is ready
                    onloaded();
                }
            }
        }
    }
    else
    {
        isRunning = false;
    }
    
}




////////////////////////////////////////////////



void Game::onloaded()
{
    
}

void Game::earlyUpdate()
{
    Camera3d::update();

    totalPolygons.clear();
    
    for(int i = 0; i < entities3d.size(); i++)
    {
        entities3d[i]->update();
        int len = entities3d[i]->polygons.size();
        for(int j = 0; j < len; j++)
        {
            entities3d[i]->polygons[j]->calculateWorldPos(entities3d[i]->rotation, entities3d[i]->position);
            entities3d[i]->polygons[j]->calculateCameraView();
            //totalPolygons.push_back(entities3d[i]->polygons[j]);
            
            std::list<Polygon*> clippedTriangles = entities3d[i]->polygons[j]->getZClippedTriangles();

            for (Polygon* clippedTriangle : clippedTriangles)
            {
                totalPolygons.push_back(clippedTriangle);
            }
            /* */
        }
    }
    int a = 1;
    
    
    /**/
    
    //std::sort(totalPolygons.begin(), totalPolygons.end(), Polygon::sortZ);
    
}

void Game::lateUpdate()
{
    
}

void Game::update(int dt)
{
    earlyUpdate();
    lateUpdate();
    
}

void Game::draw(int dt)
{
    //cube->draw();
    //player->draw();
    //totalPolygons.sortOn("averageZ", Array.DESCENDING);
    int len = totalPolygons.size();
    for(int i = 0; i < len; i++)
    {
        totalPolygons[i]->calculateScreenPos();
        //remove this if you want to see through the polygon
        if(totalPolygons[i]->normalZ < 0)
        {
            totalPolygons[i]->draw();
        }
        delete totalPolygons[i];
    }
    
}




void Game::render(int dt){

    if(useGPU)
    {
        //this is for using the renderer. we want to paint pixel to the screen!!!
        
       SDL_SetRenderDrawColor(SDL_Utils::renderer, r, g, b, 255);
       SDL_RenderClear(SDL_Utils::renderer);

       ///this is where we handle out game in the MyGame clas - the actual implementation
       draw(dt);
       ////
       SDL_RenderPresent(SDL_Utils::renderer);
    }
    else
    {
        SDL_LockSurface(SDL_Utils::gScreenSurface);
        //clear screen!
        SDL_memset(SDL_Utils::gScreenSurface->pixels, 0, SDL_Utils::gScreenSurface->h * SDL_Utils::gScreenSurface->pitch);
        draw(dt);

        
        SDL_UnlockSurface(SDL_Utils::gScreenSurface);

        SDL_UpdateWindowSurface(SDL_Utils::window);
    }
    /*
     
     */
}
void Game::clean(){
    
    SDL_DestroyWindow(SDL_Utils::window);
    SDL_DestroyRenderer(SDL_Utils::renderer);
    SDL_Quit();
}


void Game::handleEvents(){
    
    SDL_PollEvent(&SDL_Utils::event);
    switch (SDL_Utils::event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            switch (SDL_Utils::event.key.keysym.sym){
                case SDLK_w:
                    Keybaord::W = true;
                    break;
                case SDLK_a:
                    Keybaord::A = true;
                    break;
                case SDLK_s:
                    Keybaord::S = true;
                    break;
                case SDLK_d:
                    Keybaord::D = true;
                    break;
                default:
                    break;
            }
            
            break;
        case SDL_KEYUP:
            switch (SDL_Utils::event.key.keysym.sym){
                case SDLK_w:
                    Keybaord::W = false;
                    break;
                case SDLK_a:
                    Keybaord::A = false;
                    break;
                case SDLK_s:
                    Keybaord::S = false;
                    break;
                case SDLK_d:
                    Keybaord::D = false;
                    break;
                default:
                    break;
            }
            break;
            
        default:
            break;
    }
    
}


//load in json and save it as out own data structure, much faster
void Game::parseJsonToMap(Json::Value &data, std::map<std::string,Frame> &frames, int &numZeros)
{
    Json::Value f = (data)["frames"];
    for( Json::Value::const_iterator itr = f.begin() ; itr != f.end() ; itr++ )
    {
        std::string key = itr.key().asString();
        Frame frame;
        Json::Value frameObj = f[key];
        Json::Value list = frameObj["frame"];
        frame.x = list["x"].asInt();
        frame.y = list["y"].asInt();
        frame.w = list["w"].asInt();
        frame.h = list["h"].asInt();
        
        
        frame.destW = frame.w;
        frame.destH = frame.h;
        
        frames.emplace(key, frame);
               
    }
    
    numZeros = data["meta"]["numZeros"].asInt();
}


void Game::loadAssetFromDisk(std::string dirName)
{
    //save json and texture in map for later retrival
    if(assetsMap.find( dirName ) == assetsMap.end())
    {
        AtlasObj *o = new AtlasObj();
        std::string jsonPath = "/Users/yonnizohar/Desktop/c++ projects/SdlTest/SdlTest/assets/"+dirName+"/ta.json";
        JsonHandler::loadJson(jsonPath, &o->data);
        
        parseJsonToMap(o->data,o->frames, o->numZeros);
        
        std::string imgPath = "/Users/yonnizohar/Desktop/c++ projects/SdlTest/SdlTest/assets/"+dirName+"/ta.png";
        SDL_Surface* surface = TextureManager::getSurface(imgPath);
        o->texture = TextureManager::getTexture(surface);
        TextureManager::freeSurface(surface);
        assetsMap.emplace(dirName, o);
        
    }
}

///////////3d methods////////////////
