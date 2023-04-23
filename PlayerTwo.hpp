#pragma once
#include "Entity.hpp"
using namespace std;
class BulletObject;
class Entity;
class Map;
class RenderWindow;
class ThreatObject;
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
class PlayerTwo
{
public :
    PlayerTwo(int posX_,int posY_,const char* file);
    const  float PLAYER_WIDTH  = 32 ;
    const  float PLAYER_HEIGHT = 32;
    const int step=3;
    void handleEvent(SDL_Event& event);
    void move(Map& gamemap);
    void render();
    bool checkCollision(Map& gamemap);
    void handleInputAction(SDL_Event& event,PlayerTwo& player);

    void handleBullet(Map& gamemap,PlayerTwo& player,vector<ThreatObject*> threat_list);
    bool meet_enemy(BulletObject* p_bullet,ThreatObject* p_threat);
    bool touch_enemy(ThreatObject* p_threat);

    int posX,posY,velX,velY;
    int lastPosX,lastPosY;
    int status = UP;
    SDL_Texture* tex;
    bool is_alive;

    int lives;
private:
    vector<BulletObject*> p_bullet_list;
};

