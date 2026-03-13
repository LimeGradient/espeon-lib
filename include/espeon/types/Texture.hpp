#pragma once

#include <string>

#include <SDL3/SDL.h>

#include "espeon/backend/BackendRenderer.hpp"

namespace espeon {
    class Texture {
    public:
        Texture(std::string path) {
            this->texture = BackendRenderer::get()->loadImage(path);
        }

        bool isVisible() {
            return this->visible;
        }

        void setVisible(bool visible) {
            this->visible = visible;
        }

        SDL_Texture* getTexture() {
            return this->texture;
        }
    
    private:
        SDL_Texture* texture;
        bool visible;
    };
}