
#pragma once
#include "RenderWindow.hpp"
#include <vector>
 #include <stdint.h>
class Common_Func
{
public:
    static SDL_Texture* loadTexture(const char* file_path);
    static void draw(SDL_Texture* tex,SDL_Rect src,SDL_Rect dest);
    static void runMenu();
    SDL_Texture* image_menu=NULL;

};
