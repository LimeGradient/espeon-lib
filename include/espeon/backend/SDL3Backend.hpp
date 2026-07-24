#pragma once

#include <SDL3/SDL.h>

#include "espeon/backend/types/Color.hpp"
#include "espeon/backend/types/Vector2.hpp"
#include "espeon/util/Singleton.hpp"

namespace espeon {
    class SDL3Backend : public util::Singleton<SDL3Backend> {
    public:
        void createContext(SDL_Window* window, SDL_Renderer* renderer) {
            this->window = window;
            this->renderer = renderer;
        }

        void drawRectangle(Vector2 pos, Vector2 size, SDL_Color fillColor);
        
        SDL_Rect createRect(Vector2 pos, Vector2 size);
        SDL_Color colorToSDLColor(Color color);
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
    };
}