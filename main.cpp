
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_ttf.h>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Map.hpp"
#include "BulletObject.hpp"
#include "Game.hpp"
#include "ThreatObject.hpp"
#include "MenuGame.hpp"
const int enemy_quantity = 3;
// Define constants for the size and position of buttons


using namespace std;



const int FPS = 60;
const int frameDelay= 1000/ FPS;

Uint32 frameStart;
int frameTime;

vector<ThreatObject*> make_threat_list(Map& gamemap)
{
    vector<ThreatObject*> list_threat;
    for(int i = 0;i < enemy_quantity;i++)
    {
        ThreatObject* p_object = new ThreatObject[enemy_quantity];
        p_object->rect.x = 1000;
        p_object->rect.y = 150*i;
        while(p_object->checkToMap(gamemap))
        {
            p_object->rect.y += 100;
        }

        list_threat.push_back(p_object);

    }
    return list_threat;
}
Button createButton(const char* imagePath, int x, int y,RenderWindow window) {
    // Tạo nút mới
    Button button;

    // Tải hình ảnh và chuyển đổi thành texture
    button.texture = window.loadTexture(imagePath);
    if (button.texture == NULL) {
        std::cout << "Failed to load button image"<<endl;
    }

// Lấy thông tin kích thước của texture
SDL_QueryTexture(button.texture, NULL, NULL, &button.rect.w, &button.rect.h);

// Đặt vị trí của nút
button.rect.x = x;
button.rect.y = y;

return button;
}


int main(int argc,char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Event e;


    RenderWindow window("game Tank",RenderWindow::SCREEN_WIDTH,RenderWindow::SCREEN_HEIGHT);


    SDL_Texture* image =window.loadTexture("res/tankres/Hull_01_W.png");
    Entity player1(0,320,"res/tankres/Hull_01_W.png");

    Map gamemap;

    gamemap.loadMap("res/map_level/map2.csv");
    gamemap.loadTileSet("temp.png","res/blank.png");


    Game NewGame;

    //////////////
    vector<ThreatObject*> threat_list = make_threat_list(gamemap);
     bool gameRunning= false;

    bool quit = false;
    SDL_Texture* menu_pic = window.loadTexture("res/Menu/menu_pic.png");
    MenuGame menu;
    Button playButton = createButton("res/Menu/play_button.png",BUTTON_X,BUTTON_Y,window);
    Button quitButton = createButton("res/Menu/quit_button.png",BUTTON_X,BUTTON_Y + BUTTON_MARGIN,window);
    Button level1 = createButton("res/Menu/map1_button.png",BUTTON_X,BUTTON_Y,window);
    Button level2 = createButton("res/Menu/map2_button.png",BUTTON_X + BUTTON_MARGIN* 2,BUTTON_Y,window);
    Button mode_com = createButton("res/Menu/MODE COM.png",BUTTON_X,BUTTON_Y,window);
    Button mode_player = createButton("res/Menu/Mode Player.png",BUTTON_X + BUTTON_MARGIN* 2,BUTTON_Y,window);
    while(!quit)
    {
        menu.runMenu(e,playButton,quitButton,quit,gameRunning,window,menu_pic);
    }
    quit = false;
    while(!quit && gameRunning)
    {
        menu.chooseLevel(e,level1,level2,quitButton,quit,gameRunning,window,menu_pic,gamemap);
    }
    while(gameRunning )
        {

            frameStart=SDL_GetTicks();

            SDL_RenderClear(window.renderer);

                gamemap.drawMap();
                //check event from keyboard or mouse
                while( SDL_PollEvent( &e ) != 0 )
                {

                //User requests quit
                            if( e.type == SDL_QUIT )
                            {
                                gameRunning=false;
                            }

                            //Handle input for player
                            if(player1.is_alive)
                            {
                                player1.handleEvent(e);
                                player1.handleInputAction(e,player1);
                            }
                            if(1 > 2 )
                            {
                                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"Well played!","You won !",window.window);
                                gameRunning = false;
                                break;

                            }
                }


                player1.handleBullet(gamemap,player1,threat_list);

                for(int i = 0;i < enemy_quantity;i++)
                {
                    if(threat_list[i]->is_alive)
                    {
                        threat_list[i]->make_bullet(threat_list[i]);
                        threat_list[i]->RandomShot(gamemap,player1,threat_list[i]);
                        threat_list[i]->moveRandomly(gamemap,player1,threat_list[i]);
                        threat_list[i]->render();
                    }
                }

                if(player1.is_alive)
                {
                    player1.move(gamemap);
                    player1.render(player1.tex);
                }

                if(!player1.is_alive)
                {
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Game over!", "Better next time!",window.window);
                    break;
                }



                frameTime =SDL_GetTicks() - frameStart;




            if(frameDelay  > frameTime)
            {
                SDL_Delay(frameDelay - frameTime);
            }

            window.display();
            window.clear();
        }


    window.cleanUp();
    SDL_DestroyTexture(menu_pic);
    SDL_DestroyTexture(playButton.texture);
    SDL_DestroyTexture(quitButton.texture);
    SDL_DestroyTexture(level1.texture);
    SDL_DestroyTexture(level2.texture);
    return 0;
}






