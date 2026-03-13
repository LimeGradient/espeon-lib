#pragma once

#include <string>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "espeon/types/Vector2.hpp"

namespace espeon {
    class BackendRenderer {
    public:
        static BackendRenderer* get() {
            static BackendRenderer instance;
            return &instance;
        }

        void setup(SDL_Renderer* renderer) {
            this->renderer = renderer;
            this->textEngine = TTF_CreateRendererTextEngine(this->renderer);
        }

        SDL_Renderer* getRenderer() {
            return this->renderer;
        }

        TTF_TextEngine* getTextEngine() {
            return this->textEngine;
        }

        SDL_FRect drawPrimitive(Vector2 pos, Vector2 size, SDL_Color outlineColor);
        SDL_FRect drawFilledPrimitive(Vector2 pos, Vector2 size, SDL_Color outlineColor, SDL_Color fillColor);

        SDL_Texture* loadImage(std::string path);

        SDL_FPoint getCenter(SDL_Texture* texture) {
            SDL_FPoint center = {texture->w / 2.f, texture->h / 2.f};
            return center;
        }

        SDL_FRect textureToRect(SDL_Texture* texture);
        void setRectPos(SDL_FRect* rect, Vector2 pos);
    
    private:
        SDL_Renderer* renderer;
        TTF_TextEngine* textEngine;
    };
}