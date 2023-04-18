#ifndef ENITY_
#define ENITY_


#include <iostream>
#include <SDL.h>
#include<vector>
#include <SDL_image.h>
#include "Map.hpp"
#include "BulletObject.hpp"
#include "Game.hpp"
#include "ThreatObject.hpp"

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
using namespace std;

class BulletObject;
class Map;
class Game;
class ThreatObject;
class Entity
{
public:
    Entity();
    const  float PLAYER_WIDTH  = 32 ;
    const  float PLAYER_HEIGHT = 32;

    const int step=4;


    void handleEvent(SDL_Event& event);
    void move(Map& gamemap,Game& game);
    void render(SDL_Texture* tex);
    bool checkCollision(Map& gamemap,Game& game);


    void handleInputAction(SDL_Event& event,Entity& player);
    void handleBullet(Map& gamemap,Entity& player,vector<ThreatObject*> threat_list);
    bool meet_enemy(BulletObject* p_bullet,ThreatObject* p_threat);
    bool touch_enemy(ThreatObject* p_threat);





    int posX,posY,velX,velY;
    int lastPosX,lastPosY;
    int status = UP;
    SDL_Texture* tex;
    bool is_alive;
    bool gain_star;
    int lives;

private:
    vector<BulletObject*> p_bullet_list;
};
#endif // ENITY_