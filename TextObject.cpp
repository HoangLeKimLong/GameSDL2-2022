#include "TextObject.hpp"
#include "SDL_ttf.h"

TextObject::TextObject()
{
    text_color.r = 255;
    text_color.g = 255;
    text_color.b = 255;
    texture_ = NULL;

}
TextObject::~TextObject()
{

}

bool TextObject::loadFromRenderText(TTF_Font* font)
{
    SDL_Surface* text_surface /*= TTF_RenderText_Solid(font,string_val.c_str(),text_color) */;
    if( text_surface != NULL)
    {
        texture_ = SDL_CreateTextureFromSurface(RenderWindow::renderer,text_surface);
        width  = text_surface->w;
        height = text_surface->h;
        SDL_FreeSurface(text_surface);

    }
    return texture_ != NULL;
}
void TextObject::Free()
{
    if(texture_ != NULL)
    {
        SDL_DestroyTexture(texture_);
        texture_ = NULL;
    }

}
void TextObject::setColor(Uint32 red,Uint32 green,Uint32 blue)
{
    text_color.r = red;
    text_color.g = green;
    text_color.b = blue;
}
void TextObject::setColorType(int type)
{
    SDL_Color new_color;
    switch(type)
    {
        case Red_Text:
            new_color = { 255,0,0};
            text_color = new_color;
            break;
        case White_Text:
            new_color = { 255,255,0};
            text_color = new_color;
            break;
        case Black_text:
            new_color = { 0,0,0};
            text_color = new_color;
            break;
    }
}
