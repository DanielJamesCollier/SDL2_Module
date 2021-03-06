#ifndef SDL_MODULE_HPP
#define SDL_MODULE_HPP

// dependancies
#include "SDL2/SDL.h"

// std
#include <string>
#include <stdexcept>

//------------------------------------------------------------
//                       sdl_module                         //
//------------------------------------------------------------

class sdl_module final {
public:
//                         RAII                             // 
//------------------------------------------------------------
    sdl_module(std::string title, int dpi_unscaled_width, int dpi_unscaled_height) noexcept(false);
    sdl_module(std::string title, int x, int y,  int dpi_unscaled_width, int dpi_unscaled_height) noexcept(false);
    ~sdl_module();
    
//                       functions                         // 
//------------------------------------------------------------
    void poll_events();

private:
    void get_display_dpi(int display_index, float *dpi, float *default_dpi);

//                         data                             // 
//------------------------------------------------------------
    std::string m_title;
    int m_x;
    int m_y;
    int m_dpi_scaled_width;
    int m_dpi_scaled_height;
    int m_renderer_width;
    int m_renderer_height;

    SDL_Window *m_window;
    SDL_Renderer *m_renderer;

public:
    SDL_Event m_event;

}; // sdl_module 



//------------------------------------------------------------
//                  sdl_module_exception                    //
//------------------------------------------------------------

class sdl_module_exception : public std::runtime_error {
public:
//                         RAII                             // 
//------------------------------------------------------------
    explicit sdl_module_exception(std::string what);
    explicit sdl_module_exception(const char* what);

}; // sdl_module_exception

#endif // SDL_MODULE_HPP
