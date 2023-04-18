
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

const int enemy_quantity = 3;
// Các hằng số định nghĩa kích thước và vị trí của các nút
const int BUTTON_WIDTH = 200;
const int BUTTON_HEIGHT = 100;
const int BUTTON_MARGIN = 150;
const int BUTTON_X = 500;
const int BUTTON_Y = 270;

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

struct Button {
    SDL_Texture* texture;   // Hình ảnh của nút
    SDL_Rect rect;          // Vị trí và kích thước của nút
};
Button createButton(const char* imagePath, int x, int y,RenderWindow window);
int main(int argc,char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Event e;


    RenderWindow window("game Tank",RenderWindow::SCREEN_WIDTH,RenderWindow::SCREEN_HEIGHT);


    SDL_Texture* image =window.loadTexture("res/tankres/Hull_01_W.png");
    Entity player;
    player.tex=image;

    player.posX=0;
    player.posY=0;

    Map gamemap;

    gamemap.loadMap("res/map_level/1.csv");
    gamemap.loadTileSet("temp.png","res/blank.png");


    Game NewGame;



    //////////////
    vector<ThreatObject*> threat_list = make_threat_list(gamemap);
     bool gameRunning= false;

    bool quit = false;
    SDL_Texture* menu_pic = window.loadTexture("res/Menu/menu_pic.png");

    Button playButton = createButton("res/Menu/play_button.png",BUTTON_X,BUTTON_Y,window);
    Button quitButton = createButton("res/Menu/quit_button.png",BUTTON_X,BUTTON_Y + BUTTON_MARGIN,window);
    while(!quit)
    {
        // Xử lý sự kiện
        while (SDL_PollEvent(&e)) {
            // Nhấp chuột
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                // Kiểm tra xem chuột có trên nút Play không
                if (e.button.x >= playButton.rect.x && e.button.x <= playButton.rect.x + playButton.rect.w
                        && e.button.y >= playButton.rect.y && e.button.y <= playButton.rect.y + playButton.rect.h) {
                    std::cout << "Play button clicked!" << std::endl;
                    gameRunning = true;
                    quit = true;
                }
                // Kiểm tra xem chuột có trên nút Quit không
                else if (e.button.x >= quitButton.rect.x && e.button.x <= quitButton.rect.x + quitButton.rect.w
                        && e.button.y >= quitButton.rect.y && e.button.y <= quitButton.rect.y + quitButton.rect.h) {
                    quit = true;
                }
            }
            // Nhấn phím ESC
            else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
            }
            // Sự kiện thoát khỏi cửa sổ
            else if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Xóa màn hình
        SDL_RenderClear(window.renderer);

        // Vẽ các nút lên màn hình
        SDL_Rect dest = { 0,0,1280,640};
        SDL_RenderCopy(window.renderer,menu_pic,NULL,&dest);
        SDL_RenderCopy(window.renderer, playButton.texture, NULL, &playButton.rect);
        SDL_RenderCopy(window.renderer, quitButton.texture, NULL, &quitButton.rect);

        // Cập nhật màn hình
        SDL_RenderPresent(window.renderer);
        SDL_Delay(300);
    }
    SDL_DestroyTexture(menu_pic);
    SDL_DestroyTexture(playButton.texture);
    SDL_DestroyTexture(quitButton.texture);
    while(gameRunning )
        {

            frameStart=SDL_GetTicks();
            SDL_SetRenderDrawColor(RenderWindow::renderer,160, 69, 19, 255);
            SDL_RenderClear(window.renderer);
            SDL_SetRenderDrawColor(RenderWindow::renderer,160, 69, 19, 255);
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
                            if(player.is_alive)
                            {
                                player.handleEvent(e);
                                player.handleInputAction(e,player);
                            }
                            if(1 > 2 )
                            {
                                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"Well played!","You won !",window.window);
                                gameRunning = false;
                                break;

                            }
                }


                player.handleBullet(gamemap,player,threat_list);

                for(int i = 0;i < enemy_quantity;i++)
                {
                    if(threat_list[i]->is_alive)
                    {
                        threat_list[i]->make_bullet(threat_list[i]);
                    }
                }
                for(int i = 0;i < enemy_quantity;i++)
                {
                    threat_list[i]->RandomShot(gamemap,player,threat_list[i]);

                }
                if(player.is_alive)
                {
                    player.move(gamemap,NewGame);
                }
                for(int i = 0;i < enemy_quantity;i++)
                {
                    if(threat_list[i]->is_alive)
                    {
                        threat_list[i]->moveRandomly(gamemap,player,threat_list[i]);
                    }
                }


                if(player.is_alive)
                {
                    player.render(player.tex);

                }

                for(int i = 0;i < enemy_quantity;i++)
                {
                    if(threat_list[i]->is_alive)
                    {
                        threat_list[i]->render();
                    }
                }


                frameTime =SDL_GetTicks() - frameStart;




                window.display();
                window.clear();
            if(!player.is_alive)
            {
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Game over!", "Better next time!",window.window);
                break;
            }

            if(frameDelay  > frameTime)
            {
                SDL_Delay(frameDelay - frameTime);
            }


        }


    window.cleanUp();
    return 0;
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
