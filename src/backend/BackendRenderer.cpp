#include "espeon/backend/BackendRenderer.hpp"

namespace espeon {
    SDL_FRect BackendRenderer::drawPrimitive(Vector2 pos, Vector2 size, SDL_Color outlineColor) {
        SDL_FRect rect;
        SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
        SDL_RenderClear(this->renderer);

        SDL_SetRenderDrawColor(this->renderer, outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a);
        rect.x = pos.x;
        rect.y = pos.y;
        rect.w = size.x;
        rect.h = size.y;

        return rect;
    }

    SDL_Texture* BackendRenderer::loadImage(std::string path) {
        SDL_Texture* texture = IMG_LoadTexture(this->renderer, path.c_str());
        return texture;
    }

    SDL_FRect BackendRenderer::textureToRect(SDL_Texture* texture) {
        SDL_FRect rect = {
            0, 0, static_cast<float>(texture->w), static_cast<float>(texture->h)
        };
        return rect;
    }

    void BackendRenderer::setRectPos(SDL_FRect* rect, Vector2 pos) {
        rect->x = pos.x;
        rect->y = pos.y;
    }
}