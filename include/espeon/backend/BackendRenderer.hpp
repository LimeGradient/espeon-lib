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

        void setup(SDL_Window* window, SDL_Renderer* renderer) {
            this->window = window;
            this->renderer = renderer;
            this->textEngine = TTF_CreateRendererTextEngine(this->renderer);
        }

        void updateRenderer() {
            SDL_RenderClear(this->renderer);
            SDL_RenderPresent(this->renderer);
        }

        SDL_Texture* loadImage(std::string path);
        
        SDL_FPoint getLogicalMousePos();

        SDL_FPoint getCenter(SDL_Texture* texture) {
            SDL_FPoint center = {texture->w / 2.f, texture->h / 2.f};
            return center;
        }

        SDL_FPoint getCenter(SDL_FRect* rect) {
            SDL_FPoint center = {(rect->w / 2.f) + rect->x, (rect->h / 2.f) + rect->y};
            return center;
        }

        SDL_FPoint getCenter(SDL_FRect* rect, SDL_FRect* inner) {
            SDL_FPoint center = {
                rect->x + ((rect->w - inner->w) / 2),
                rect->y + ((rect->h - inner->h) / 2)
            };
            return center;
        }

        SDL_FRect textureToRect(SDL_Texture* texture);
        void setRectPos(SDL_FRect* rect, Vector2 pos);

        SDL_Rect floatRectToRect(SDL_FRect rect);
        
        SDL_Window* getWindow() {
            return this->window;
        }

        SDL_Renderer* getRenderer() {
            return this->renderer;
        }

        TTF_TextEngine* getTextEngine() {
            return this->textEngine;
        }

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        TTF_TextEngine* textEngine;
    };
}