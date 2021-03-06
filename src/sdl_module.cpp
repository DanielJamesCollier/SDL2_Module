#include "sdl_module.hpp"

//------------------------------------------------------------
//                       sdl_module                         //
//------------------------------------------------------------


//                         RAII                             // 
//------------------------------------------------------------
sdl_module::sdl_module(std::string title, int dpi_unscaled_width, int dpi_unscaled_height) noexcept(false) 
:   m_title{std::move(title)}
,   m_x{SDL_WINDOWPOS_CENTERED}
,   m_y{SDL_WINDOWPOS_CENTERED}
,   m_dpi_scaled_width{}
,   m_dpi_scaled_height{} {
    
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        throw sdl_module_exception(SDL_GetError());
    }
        
    float dpi, default_dpi;

    get_display_dpi(0, &dpi, &default_dpi);

    m_dpi_scaled_width = static_cast<int>(dpi_unscaled_width * dpi / default_dpi);
    m_dpi_scaled_height = static_cast<int>(dpi_unscaled_height * dpi / default_dpi);

    Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI;

    if ((m_window = SDL_CreateWindow(m_title.c_str(), m_x, m_y, m_dpi_scaled_width, m_dpi_scaled_height, flags)) == nullptr) {
        throw sdl_module_exception(std::string(SDL_GetError()));
    }

    if ((m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED)) == nullptr) {
        throw sdl_module_exception(std::string(SDL_GetError()));
    }

    if (SDL_GetRendererOutputSize(m_renderer, &m_renderer_width, &m_renderer_height) < 0) {
        throw sdl_module_exception(std::string(SDL_GetError()));
    }
    
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
    SDL_RenderPresent(m_renderer);
}

//------------------------------------------------------------
sdl_module::sdl_module(std::string title, int x, int y, int dpi_unscaled_width, int dpi_unscaled_height) noexcept(false) 
:   m_title{std::move(title)}
,   m_x{x}
,   m_y{y}
,   m_dpi_scaled_width{}
,   m_dpi_scaled_height{} {
    
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        throw sdl_module_exception(SDL_GetError());
    }
        
    float dpi, default_dpi;

    get_display_dpi(0, &dpi, &default_dpi);

    m_dpi_scaled_width = static_cast<int>(dpi_unscaled_width * dpi / default_dpi);
    m_dpi_scaled_height = static_cast<int>(dpi_unscaled_height * dpi / default_dpi);

    Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI;

    if ((m_window = SDL_CreateWindow(title.c_str(), m_x, m_y, m_dpi_scaled_width, m_dpi_scaled_height, flags)) == nullptr) {
        throw sdl_module_exception(std::string(SDL_GetError()));
    }

    if ((m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED)) == nullptr) {
        throw sdl_module_exception(std::string(SDL_GetError()));
    }

    if (SDL_GetRendererOutputSize(m_renderer, &m_renderer_width, &m_renderer_height) < 0) {
        throw sdl_module_exception(std::string(SDL_GetError()));
    }
    
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
    SDL_RenderPresent(m_renderer);
}

//------------------------------------------------------------
sdl_module::~sdl_module() {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

//                       functions                         // 
//------------------------------------------------------------
void
sdl_module::poll_events() {
    
}

void 
sdl_module::get_display_dpi(int display_index, float *dpi, float *default_dpi) {
    const float system_default_dpi =
    #ifdef __APPLE__
        72.0f;
    #elif defined(_WIN32)
        96.0f;
    #else
        static_assert(false, "No system default DPI set for this platform.");
    #endif

    if (SDL_GetDisplayDPI(display_index, NULL, dpi, NULL) != 0) {
        if (dpi) *dpi = system_default_dpi;
    }

    if (default_dpi) {
        *default_dpi = system_default_dpi;
    }
}


//------------------------------------------------------------
//                  sdl_module_exception                    //
//------------------------------------------------------------

//                         RAII                             // 
//------------------------------------------------------------
sdl_module_exception::sdl_module_exception(std::string what)
:   std::runtime_error(what) {
    SDL_Quit();
}

sdl_module_exception::sdl_module_exception(const char *what)
:   std::runtime_error(what) {
    SDL_Quit();
}


