#pragma once
#include <SDL_ttf.h>
#include "Common_Func.hpp"
#include "BulletObject.hpp"
#include "Entity.hpp"
#include "Game.hpp"
#include "Map.hpp"
#include "ThreatObject.hpp"
#include "RenderWindow.hpp"

class BulletObject;
class Entity;
class Game;
class Map;
class ThreatObject;
class RenderWindow;
using namespace std;
class TextObject
{
public:
    TextObject();
    ~TextObject();

    enum TextColor
    {
        Red_Text = 0,
        White_Text = 1,
        Black_text =2,
    };

    bool loadFromRenderText(TTF_Font* font);
    void Free();
    void setColor(Uint32 red,Uint32 green,Uint32 blue);
    void setColorType(int type);

    void renderText(int xpos,int ypos
                    ,SDL_Rect* clip = NULL,
                    double angle = 0.0,
                    SDL_Point* center = NULL,
                    SDL_RendererFlip flip = SDL_FLIP_NONE);
    int getWidth(){ return width;}
    int getHeigt(){ return height;}

    void setText( const string& text) { string_val = text;}
    string getText() const { return string_val ;}
private:
    string string_val;
    SDL_Color text_color;
    SDL_Texture* texture_;
    int width;
    int height;
};
