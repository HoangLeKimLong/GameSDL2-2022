
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Map.hpp"
#include "BulletObject.hpp"
#include "ThreatObject.hpp"
#include "MenuGame.hpp"
#include "Common_Func.hpp"
const int enemy_quantity = 3;
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
        p_object->rect.y = 280*i;
        while(p_object->checkToMap(gamemap))
        {
            p_object->rect.y += 200;
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

    Entity player1(0,320,"res/tankres/Hull_01_W.png",1 );
    Entity player2(1216,320,"res/tankres/new_player/Hull_01_W.png",2);
    Map gamemap;

    gamemap.loadMap("res/map_level/map2.csv");
    gamemap.loadTileSet("temp.png","res/coin_blank.png");
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
    Button help = createButton("res/Menu/help_button.png",BUTTON_X + BUTTON_MARGIN*2,BUTTON_Y,window);
    Button x_ = createButton("res/Menu/x_button.png",1000,50,window);
    while(!quit)
    {
        if(!menu.tutorial)
        {
            menu.runMenu(e,playButton,quitButton,help,quit,gameRunning,window,menu_pic);
        }
        else
        {
            menu.run_tutorial(e,window,quit,x_,gameRunning);
        }

    }
        quit = false;
        while(!quit&& gameRunning)
        {
            menu.chooseMode(e,mode_com,mode_player,quitButton,quit,gameRunning,window,menu_pic);

        }
        quit = false;
        if( menu.mode == 0)
        {
                 while(!quit && gameRunning)
            {
                menu.chooseLevel(e,level1,level2,quitButton,quit,gameRunning,window,menu_pic,gamemap);
            }
        }

        if( menu.mode == modeBot) // play with bot
        {
            while(gameRunning )
            {
                SDL_RenderClear(window.renderer);

                    menu.runGameWithBot(e,gamemap,gameRunning,player1,threat_list,enemy_quantity,window);
                    if(!player1.is_alive)
                    {
                        gameRunning = false;
                    }
                Common_Func::handleFPS(FPS,frameDelay,frameStart,frameTime);
                window.display();
                window.clear();
            }
            if(player1.gain_coin)
            {
                menu_pic = window.loadTexture("res/Menu/WinBot.png");
            }
            else
            {
                menu_pic = window.loadTexture("res/Menu/LoseBot.png");
            }
            if(player1.gain_coin || !player1.is_alive)
            {
                quit = false;
                quitButton.rect.x =  600;
                quitButton.rect.y = 300;
                SDL_Rect dest = { 0,0,1280,640};
                    while( !quit)
                        {
                            while (SDL_PollEvent(&e)) {
                        // Nhấp chuột
                            if (e.type == SDL_MOUSEBUTTONDOWN) {
                             // Kiểm tra xem chuột có trên nút Quit không
                                if (e.button.x >= quitButton.rect.x && e.button.x <= quitButton.rect.x + quitButton.rect.w
                                    && e.button.y >= quitButton.rect.y && e.button.y <= quitButton.rect.y + quitButton.rect.h) {

                                quit = true;
                                }
                            }
                            SDL_RenderCopy(window.renderer,menu_pic,NULL,&dest);
                            SDL_RenderCopy(window.renderer,quitButton.texture,NULL,&quitButton.rect);
                            window.display();
                        }
                    }
            }
        }
        if( menu.mode == modePlayer)
        {

           while(gameRunning)
           {


                    SDL_RenderClear(window.renderer);

                menu.runGameWithPlayer(e,gamemap,gameRunning,player1,player2,window);
                Common_Func::handleFPS(FPS,frameDelay,frameDelay,frameTime);
                if(!player1.is_alive || !player2.is_alive)
                {
                    gameRunning = false;
                }
                window.display();
                window.clear();
           }
           if(!player1.is_alive || !player2.is_alive)

            {
                if(player1.is_alive)
                {
                    menu_pic = window.loadTexture("res/Menu/Player1won.png");
                }
                else
                {
                    menu_pic = window.loadTexture("res/Menu/Player2won.png");
                }
                quit = false;
                quitButton.rect.x = 600;
                quitButton.rect.y = 300;
                SDL_Rect dest = { 0,0,1280,640};
                    while( !quit)
                        {
                            while (SDL_PollEvent(&e)) {
                        // Nhấp chuột
                            if (e.type == SDL_MOUSEBUTTONDOWN) {
                             // Kiểm tra xem chuột có trên nút Quit không
                                if (e.button.x >= quitButton.rect.x && e.button.x <= quitButton.rect.x + quitButton.rect.w
                                    && e.button.y >= quitButton.rect.y && e.button.y <= quitButton.rect.y + quitButton.rect.h) {

                                quit = true;
                                }
                            }
                            SDL_RenderCopy(window.renderer,menu_pic,NULL,&dest);
                            SDL_RenderCopy(window.renderer,quitButton.texture,NULL,&quitButton.rect);
                            window.display();
                        }
                    }

            }

        }


    window.cleanUp();
    SDL_DestroyTexture(menu_pic);
    SDL_DestroyTexture(playButton.texture);
    SDL_DestroyTexture(quitButton.texture);
    SDL_DestroyTexture(level1.texture);
    SDL_DestroyTexture(level2.texture);
    SDL_DestroyTexture(mode_com.texture);
    SDL_DestroyTexture(mode_player.texture);
    SDL_DestroyTexture(help.texture);
    SDL_DestroyTexture(x_.texture);
    player1.clean();
    threat_list[0]->clean(threat_list);

    return 0;
}






