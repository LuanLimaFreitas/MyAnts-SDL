#include "window.h"
#include "parameters.h"
#include "globals.h"
#include <iostream>
#include <math.h>

Window::Window(std::string title, int width, int heigth):
_title(title), _width(width), _heigth(heigth)
{
    if(!init()){
        _closed = true;
    }
}

Window::~Window()
{
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyTexture(_ant_sprite);
    SDL_DestroyTexture(_droplet_sprite);

    SDL_Quit();
}

bool Window::init()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        std::cerr << "Failed to initialize SDL.\n";
        return 0;
    }

    _window = SDL_CreateWindow(
                _title.c_str(),
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                _width,
                _heigth,
                0);

    if(_window == nullptr){
        std::cerr << "Failed to create Window. :( \n";
        return 0;
    }

    _renderer = SDL_CreateRenderer(_window,-1,SDL_RENDERER_PRESENTVSYNC);

    if(_renderer == nullptr)
    {
        std::cerr << "Failed to create Renderer. :(\n";
        return 0;
    }

    SDL_SetRenderDrawColor(_renderer,220,220,220,255);

    SDL_Surface *surface = SDL_LoadBMP("/home/luan/Desktop/MyAnts-SDL/circle_black_5by5.bmp");
    if (surface == nullptr){
        SDL_DestroyRenderer(_renderer);
        SDL_DestroyWindow(_window);
        std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }
    _ant_sprite = SDL_CreateTextureFromSurface(_renderer, surface);
    SDL_FreeSurface(surface);
    if (_ant_sprite == nullptr){
        SDL_DestroyRenderer(_renderer);
        SDL_DestroyWindow(_window);
        std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }

    SDL_Surface *surface2 = SDL_LoadBMP("/home/luan/Desktop/MyAnts-SDL/shape_red_5by5.bmp");
    if (surface2 == nullptr){
        SDL_DestroyRenderer(_renderer);
        SDL_DestroyWindow(_window);
        std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }
    _droplet_sprite = SDL_CreateTextureFromSurface(_renderer, surface2);
    SDL_FreeSurface(surface2);
    if (_droplet_sprite == nullptr){
        SDL_DestroyRenderer(_renderer);
        SDL_DestroyWindow(_window);
        std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }




    return true;
}

bool Window::isClosed(){
    return _closed;
}

void Window::pollEvents(){

    SDL_Event event;

    if (SDL_PollEvent(&event)){
        switch (event.type) {
        case SDL_QUIT:
            _closed = true;
            break;
        default:
            break;
        }
    }

}

void Window::display(int cycle_count){

    float b = 2.71;
    float a = 0.01;

    float tranparency_multiplier;

    SDL_RenderClear(_renderer);

    /// Step 1: Draw the Pheromone Droplets.
    ///
    std::size_t i;
    for(i=0; i<Droplet::number_of_droplets; i++)
    {
        _droplet_sprite_pos.x = all_droplets[i].pos_x -3; // I guess '-3' is correct
        _droplet_sprite_pos.y = all_droplets[i].pos_y -3; // (But it might as well be '-2').
        tranparency_multiplier = std::pow(b,-a*all_droplets[i].elapsed_time(cycle_count));
        SDL_SetTextureAlphaMod(_droplet_sprite,255*tranparency_multiplier);
        SDL_RenderCopy(_renderer, _droplet_sprite, NULL, &_droplet_sprite_pos);
    }


    /// Step 2: Draw the Ants.
    ///
    for(i=0; i<number_of_ants; i++)
    {
        _ant_sprite_pos.x = all_ants[i]->pos_x - 3;
        _ant_sprite_pos.y = all_ants[i]->pos_y - 3;
        SDL_RenderCopy(_renderer, _ant_sprite, NULL, &_ant_sprite_pos);
    }

    SDL_RenderPresent(_renderer);
}
