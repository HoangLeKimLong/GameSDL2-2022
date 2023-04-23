
#include "PlayerTwo.hpp"

PlayerTwo::PlayerTwo(int posX_,int posY_ ,const char* file)
{
    posX=posX_;
    posY=posY_;

    velX=0;
    velY=0;
    is_alive = true;
    lives = 3;
    tex = Common_Func::loadTexture(file);
}

void PlayerTwo::handleEvent(SDL_Event& event)
{
    //ìf a key was pressed
    if(event.type == SDL_KEYDOWN&& event.key.repeat == 0)
    {
        //Adjust the velocity
        switch(event.key.keysym.sym)
        {
        case SDLK_UP: velY-=step;
                    SDL_DestroyTexture(tex);
                    tex=Common_Func::loadTexture("res/tankres/new_player/Hull_01_W.png");
                    status = UP;
                    break;
        case SDLK_DOWN:velY+=step;
                    SDL_DestroyTexture(tex);
                    tex=Common_Func::loadTexture("res/tankres/new_player/Hull_01_S.png");
                    status = DOWN;
                    break;
        case SDLK_LEFT: velX-=step;
                    SDL_DestroyTexture(tex);
                    tex=Common_Func::loadTexture("res/tankres/Hull_01_A.png");
                    status = LEFT;
                    break;
        case SDLK_RIGHT: velX+=step;
                    SDL_DestroyTexture(tex);
                    tex = Common_Func::loadTexture("res/tankres/new_player/Hull_01_D.png");
                    status = RIGHT;
                    break;
        }

    }




    if( event.type == SDL_KEYUP&& event.key.repeat == 0 )
    {
        //Adjust the velocity
        switch(event.key.keysym.sym)
        {
        case SDLK_UP: velY+=step; break;
        case SDLK_DOWN: velY-=step; break;
        case SDLK_LEFT: velX+=step; break;
        case SDLK_RIGHT: velX-=step; break;
        }
    }

}
