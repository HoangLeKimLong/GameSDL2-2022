
#include "MenuGame.hpp"
MenuGame::MenuGame()
{
    play = false;
}
MenuGame::~MenuGame()
{

}
void MenuGame::makeButton(const char* play_img,const char* quit_img)
{
    start_button.createButton(play_img,BUTTON_X,BUTTON_Y);
    quit_button.createButton(quit_img,BUTTON_X , BUTTON_Y + BUTTON_MARGIN);
}
void MenuGame::runMenu(SDL_Event& ev)
{
    bool quit = false;
    while( !quit )
    {
        // handle action
        while(SDL_PollEvent(&ev))
        {
            // if press mousebutton
            if(ev.type == SDL_MOUSEBUTTONDOWN)
            {
                 if (ev.button.x >= start_button.rect.x && ev.button.x <= start_button.rect.x + start_button.rect.w
                        && ev.button.y >= start_button.rect.y && ev.button.y <= start_button.rect.y + start_button.rect.h) {
                    std::cout << "Play button clicked!" << std::endl;
                    play = true;
                    quit = true;
                }
            }
            // Kiểm tra xem chuột có trên nút Quit không
                else if (ev.button.x >= quit_button.rect.x && ev.button.x <= quit_button.rect.x + quit_button.rect.w
                        && ev.button.y >= quit_button.rect.y && ev.button.y <= quit_button.rect.y + quit_button.rect.h) {
                    quit = true;
                    }
            // quit
            else if (ev.type == SDL_QUIT) {
                quit = true;
                }

        }
         // Xóa màn hình
            SDL_RenderClear(RenderWindow::renderer);

            // Vẽ các nút lên màn hình
            SDL_QueryTexture(start_button.texture,NULL,NULL,&start_button.rect.w,&start_button.rect.h);
            SDL_RenderCopy(RenderWindow::renderer, start_button.texture, NULL, &start_button.rect);
            SDL_RenderCopy(RenderWindow::renderer, quit_button.texture, NULL, &quit_button.rect);

            // Cập nhật màn hình
            SDL_SetRenderDrawColor(RenderWindow::renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderPresent(RenderWindow::renderer);
    }
}
