
#include "MenuGame.hpp"
MenuGame::MenuGame()
{

}
MenuGame::~MenuGame()
{

}
void MenuGame::runMenu(SDL_Event& e,Button playButton,Button quitButton,
                       bool& quit,bool& gameRunning,
                       RenderWindow window,
                       SDL_Texture* menu_pic)
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
                    gameRunning = false;
                    quit = true;
                }
            }
            // Nhấn phím ESC
            else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
            }
            // Sự kiện thoát khỏi cửa sổ
            else if (e.type == SDL_QUIT) {
                    gameRunning = false;
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
void MenuGame::chooseLevel(SDL_Event& e,Button level1,Button level2,Button quitButton
                           ,bool& quit,bool& gameRunning
                           ,RenderWindow window,
                           SDL_Texture* menu_pic,Map& gamemap)
{
    // Xử lý sự kiện
    while (SDL_PollEvent(&e)) {
            // Nhấp chuột
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                // Kiểm tra xem chuột có trên nút level1 không
                if (e.button.x >= level1.rect.x && e.button.x <= level1.rect.x + level1.rect.w
                        && e.button.y >= level1.rect.y && e.button.y <= level1.rect.y + level1.rect.h) {
                    std::cout << "Map 1 button clicked!" << std::endl;
                    gamemap.loadMap("res/map_level/1.csv");
                    quit = true;
                    }
                // Kiểm tra xem chuột có trên nút level2 không
                else if (e.button.x >= level2.rect.x && e.button.x <= level2.rect.x + level2.rect.w
                        && e.button.y >= level2.rect.y && e.button.y <= level2.rect.y + level2.rect.h) {
                    std::cout << "Map 2 button clicked!" << std::endl;
                    gamemap.loadMap("res/map_level/map2.csv");
                    quit = true;
                    }
                 // Kiểm tra xem chuột có trên nút Quit không
                else if (e.button.x >= quitButton.rect.x && e.button.x <= quitButton.rect.x + quitButton.rect.w
                        && e.button.y >= quitButton.rect.y && e.button.y <= quitButton.rect.y + quitButton.rect.h) {
                    gameRunning = false;
                    quit = true;
                    }
                }


            // Sự kiện thoát khỏi cửa sổ
            else if (e.type == SDL_QUIT) {
                gameRunning = false;
                quit = true;
            }
        }

        // Xóa màn hình
        SDL_RenderClear(window.renderer);

        // Vẽ các nút lên màn hình
        SDL_Rect dest = { 0,0,1280,640};
        SDL_RenderCopy(window.renderer,menu_pic,NULL,&dest);
        SDL_RenderCopy(window.renderer, level1.texture, NULL, &level1.rect);
        SDL_RenderCopy(window.renderer, level2.texture, NULL, &level2.rect);
        SDL_RenderCopy(window.renderer, quitButton.texture, NULL, &quitButton.rect);

        // Cập nhật màn hình
        SDL_RenderPresent(window.renderer);

}
