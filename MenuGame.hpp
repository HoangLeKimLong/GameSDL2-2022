#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "RenderWindow.hpp"
// Các hằng số định nghĩa kích thước và vị trí của các nút
#define BUTTON_WIDTH  200
#define BUTTON_HEIGHT  100
#define BUTTON_MARGIN  50
#define BUTTON_X  100
#define BUTTON_Y  200
struct Button
{
    SDL_Texture* texture;   // Hình ảnh của nút
    SDL_Rect rect;
    Button createButton(const char* imagePath, int x, int y)
    {
            // Tạo nút mới
            Button button;

            // Tải hình ảnh và chuyển đổi thành texture
            button.texture = Common_Func::loadTexture(imagePath);
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
};
class MenuGame
{
public:
    MenuGame();
    ~MenuGame();
    Button start_button;
    Button quit_button;
    void makeButton(const char* play_img,const char* quit_img);
    void runMenu(SDL_Event& ev);
    bool play ;

};
