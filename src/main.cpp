#include <iostream>

#include "sdl_module.hpp"

int main() {
    std::cout << "hello sailor!\n";

    try {
        sdl_module sdl("sdl_module", 600, 300);
        
        bool running = true; 
       
        while(running) {
           
            while (SDL_PollEvent(&sdl.m_event)) {
                
                if (sdl.m_event.type == SDL_QUIT) {
                    running = false; 
                    break;
                }
            }
        } 
    } catch (sdl_module_exception const &e) {
        std::cerr << e.what() << std::endl;

    } catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;

    } catch (...) {
    
    }

    return 0;
}
