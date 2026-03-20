#pragma once

#include "espeon/types/Vector2.hpp"
#include <SDL3/SDL.h>

namespace espeon {
    class HoverRect {
    public:
        HoverRect() = default;
        HoverRect(SDL_FRect rect) : rect(rect) {}

        bool update(SDL_FPoint mouse) {
            bool isHovered = SDL_PointInRectFloat(&mouse, &rect) == true;
            bool changed = isHovered != hovered;
            hovered = isHovered;
            return changed;
        }

        bool justEntered() const { return hovered; }
        bool justLeft() const { return !hovered; }

        SDL_FRect* getRect() {
            return &this->rect;
        }

        void setPos(Vector2 pos) {
            this->rect.x = pos.x;
            this->rect.y = pos.y;
        }

        SDL_FRect rect;

    private:
        bool hovered = false;
    };
}