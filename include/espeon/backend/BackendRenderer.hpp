#pragma once

#include "espeon/util/Singleton.hpp"

#if __has_include(<SDL3/SDL.h>)
    #define USE_SDL3 1
    #include <SDL3/SDL.h>
    #include "espeon/backend/SDL3Backend.hpp"
#endif

#include "espeon/backend/types/Color.hpp"

namespace espeon {
    class BackendRenderer : public util::Singleton<BackendRenderer> {
    public:
#if USE_SDL3
        void createContext(SDL_Window* window, SDL_Renderer* renderer);
#endif

        void drawRectangle(Vector2 pos, Vector2 size, Color fillColor);

    private:
#if USE_SDL3
        SDL3Backend* sdlBackend;
#endif
    };
}