#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "RenderWindow.hpp"
#include "Map.hpp"
// Các hằng số định nghĩa kích thước và vị trí của các nút
const int BUTTON_WIDTH = 200;
const int BUTTON_HEIGHT = 100;
const int BUTTON_MARGIN = 150;
const int BUTTON_X = 500;
const int BUTTON_Y = 270;
struct Button
{
    SDL_Texture* texture;   // Hình ảnh của nút
    SDL_Rect rect;

};


class MenuGame
{
public:
    MenuGame();
    ~MenuGame();

    void runMenu(SDL_Event& e,Button playButton,Button quitButton
                 ,bool& quit,bool& gameRunning,
                 RenderWindow window,SDL_Texture* menu_pic);

    void chooseLevel(SDL_Event& e,Button level1,Button level2,Button quitButton,
                     bool& quit,bool& gameRunning,
                     RenderWindow window,SDL_Texture* menu_pic,Map& gamemap);
    void chooseMode( SDL_Event& e,Button mode_com,Button mode_player,Button quitButton
                    ,bool& quit,bool& gameRunning,
                    RenderWindow window,SDL_Texture* menu_pic);

    enum MODE{ COM,PLAYER};
    int mode ;
};
