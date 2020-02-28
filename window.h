#ifndef WINDOW_H
#define WINDOW_H

#include "SDL2/SDL.h"
#include <string>

class Window
{

public:
    Window(std::string title, int width, int heigth);
    ~Window();

    void pollEvents();
    bool isClosed();

    void display(int cycle_count);
    void clear()
    {
        SDL_RenderClear(_renderer);
    }

private:
    bool init();

    std::string &_title;
    int _width = 800;
    int _heigth = 600;
    bool _closed = false;

    SDL_Window *_window = nullptr;
    SDL_Renderer *_renderer = nullptr;

    SDL_Texture *_ant_sprite = nullptr;
    SDL_Rect _ant_sprite_pos = {0,0,5,5};
    SDL_Texture *_droplet_sprite = nullptr;
    SDL_Rect _droplet_sprite_pos = {0,0,5,5};
};

#endif // WINDOW_H
