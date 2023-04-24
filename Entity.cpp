#include "Entity.hpp"
#include "RenderWindow.hpp"
#include "Common_Func.hpp"
#include "ThreatObject.hpp"
using namespace std;
Entity::Entity(int posX_ , int posY_ ,const char* file)
{
    posX=posX_;
    posY=posY_;

    velX=0;
    velY=0;
    is_alive = true;
    lives = 3;
    tex = Common_Func::loadTexture(file);
    status = UP;
    last_bullet_time = SDL_GetTicks();
}
void Entity::handleEvent(SDL_Event& event)
{
    //ìf a key was pressed
    if(event.type == SDL_KEYDOWN&& event.key.repeat == 0)
    {
        //Adjust the velocity
        switch(event.key.keysym.sym)
        {
        case SDLK_w: velY-=step;
                    SDL_DestroyTexture(tex);
                    tex=Common_Func::loadTexture("res/tankres/Hull_01_W.png");
                    status = UP;

                    break;
        case SDLK_s:velY+=step;
                    SDL_DestroyTexture(tex);
                    tex=Common_Func::loadTexture("res/tankres/Hull_01_S.png");
                    status = DOWN;
                    break;
        case SDLK_a: velX-=step;
                    SDL_DestroyTexture(tex);
                    tex=Common_Func::loadTexture("res/tankres/Hull_01_A.png");
                    status = LEFT;
                    break;
        case SDLK_d: velX+=step;
                    SDL_DestroyTexture(tex);
                    tex=Common_Func::loadTexture("res/tankres/Hull_01_D.png");
                    status = RIGHT;
                    break;


        }

    }




    if( event.type == SDL_KEYUP&& event.key.repeat == 0 )
    {
        //Adjust the velocity
        switch(event.key.keysym.sym)
        {
        case SDLK_w: velY+=step; break;
        case SDLK_s: velY-=step; break;
        case SDLK_a: velX+=step; break;
        case SDLK_d: velX-=step; break;
        }
    }



}
void Entity::move(Map& gamemap)
{
    lastPosX=posX;
    lastPosY=posY;
    //move left or right
    posX+=velX;
    //If the tank went too far to the right or left
    if( ( posX  < 0  ) || ( posX + PLAYER_WIDTH  + 30  > RenderWindow::SCREEN_WIDTH  ) )
    {
        //Move back
        posX -= velX;
    }
    //move up or down
    posY+=velY;
    //If the tank went too far to the up or down
    if( ( posY < 0  )  || (posY + PLAYER_HEIGHT  + 30 > RenderWindow::SCREEN_HEIGHT ) )
    {
        //Move back
        posY -= velY;
    }

    if(checkCollision(gamemap) )
       {
            posX=lastPosX;
            posY=lastPosY;
        }
}


bool Entity::checkCollision(Map& gamemap)
{
    // Calculate the position of the character on the TileMap
    int leftTile = (posX  ) / TILE_SIZE;
    int rightTile = (posX + PLAYER_WIDTH + 20) / TILE_SIZE;
    int topTile =   (posY )/ TILE_SIZE;
    int bottomTile =(posY + PLAYER_HEIGHT + 20) / TILE_SIZE;
     // check if charactes has collide with a tileset on TileMap
    for (int i = topTile ; i <= bottomTile; i++) {
        for (int j = leftTile  ; j <= rightTile; j++) {

            if (gamemap.posTileSet[i][j] != BLANK_TILE ) {
                return true; //
            }
        }
    }
    return false;
}
void Entity::render(SDL_Texture* tex)
{
    SDL_Rect rect;
    SDL_QueryTexture(tex,NULL,NULL,&rect.w,&rect.h);
    rect.x=posX;
    rect.y=posY;
    rect.w=PLAYER_WIDTH*2;

    rect.h=PLAYER_HEIGHT*2;

    SDL_RenderCopy(RenderWindow::renderer,tex,NULL,&rect);
    tex = NULL;
    SDL_DestroyTexture(tex);

    delete tex;

}
void Entity::handleInputAction(SDL_Event& event, Entity& player)
{
    // Set the time interval between bullets
    const Uint32 BULLET_INTERVAL = 1500; // 3000 milliseconds = 3 seconds

    // Get the current time
    Uint32 current_time = SDL_GetTicks();

    // Check if enough time has passed since the last bullet was fired
    if (current_time - last_bullet_time >= BULLET_INTERVAL)
    {
        if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
        {
            // if pressed Enter button, create a bullet
            if (event.key.keysym.sym == SDLK_RETURN)
            {
                BulletObject* p_bullet = new BulletObject();
                p_bullet->setPosBullet(player);
                p_bullet->is_move = true;
                p_bullet_list.push_back(p_bullet);

                // Record the time at which the bullet was created
                last_bullet_time = current_time;
            }
        }
    }
}

void Entity::handleBullet(Map& gamemap,Entity& player,vector<ThreatObject*> threat_list)
{
    for(int i=0;i< p_bullet_list.size();i++)
    {
        BulletObject* p_bullet = p_bullet_list.at(i);
        if( p_bullet == nullptr)
            {
                ++i;
                continue;
            }

        if(p_bullet->is_move && p_bullet != nullptr)
            {
                p_bullet->handleMove(gamemap,player);
                //if the bullet has collide to the map,delete it
                if(p_bullet->checkCollision(gamemap))
                    {
                        p_bullet->is_move=false;
                        p_bullet->rect.w = 0;
                        p_bullet->rect.w = 0;
                        p_bullet->texture = NULL;

                    }
                //if the bullet collided with the enemy,kill it
                for(int i = 0; i< (int)threat_list.size();i++)
                {
                    if(threat_list[i]->is_alive)
                    {
                        if(meet_enemy(p_bullet,threat_list[i]))
                        {
                            p_bullet->is_move = false;


                            SDL_DestroyTexture( threat_list[i]->enemy_tex);

                        }
                    }
                    if(p_bullet->is_move)
                    {
                        p_bullet->render();
                    }
                }

            }

           else
           {
               SDL_DestroyTexture(p_bullet->texture);
               p_bullet_list.erase(p_bullet_list.begin() + i);
               p_bullet = NULL;

               delete p_bullet;
           }

    }


}

bool Entity::meet_enemy(BulletObject* p_bullet,ThreatObject* p_threat)
{
            if( p_threat->rect.x + 30< p_bullet->rect.x + p_bullet->rect.w
               //left
                &&
            p_threat->rect.x + p_threat->rect.w - 30> p_bullet->rect.x
            //right
            &&
            p_threat->rect.y + 15< p_bullet->rect.y + p_bullet->rect.h
            //up
            &&
            //down
            p_threat->rect.y + p_threat->rect.h - 20> p_bullet->rect.y
            )
            {
                    p_threat->is_alive = false;
                    return true;

            }



    return false;
}
