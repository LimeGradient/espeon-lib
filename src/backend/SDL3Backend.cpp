#include "espeon/backend/SDL3Backend.hpp"

namespace espeon {
    void SDL3Backend::drawRectangle(Vector2 pos, Vector2 size, SDL_Color fillColor) {
        SDL_FRect rect{pos.x, pos.y, size.x, size.y};
        SDL_SetRenderDrawColor(this->renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
        SDL_RenderFillRect(this->renderer, &rect);
    }

    SDL_Color SDL3Backend::colorToSDLColor(Color color) {
        return SDL_Color{
            static_cast<Uint8>(color.r), 
            static_cast<Uint8>(color.g), 
            static_cast<Uint8>(color.b), 
            static_cast<Uint8>(color.a)
        };
    }
}