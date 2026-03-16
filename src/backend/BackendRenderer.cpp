#include "espeon/backend/BackendRenderer.hpp"

namespace espeon {
    SDL_FRect BackendRenderer::drawPrimitive(Vector2 pos, Vector2 size, SDL_Color color) {
        SDL_FRect rect;

        this->setRendererColor(color);
        rect.x = pos.x;
        rect.y = pos.y;
        rect.w = size.x;
        rect.h = size.y;

        return rect;
    }

    void BackendRenderer::renderRect(SDL_FRect rect, bool filled) {
        if (filled) {
            SDL_RenderFillRect(this->renderer, &rect);
        } else {
            SDL_RenderRect(this->renderer, &rect);
        }
    }

    void BackendRenderer::setRendererColor(SDL_Color color) {
        SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
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

    SDL_FPoint BackendRenderer::getLogicalMousePos() {
        SDL_FPoint mouseCoords;
        SDL_GetMouseState(&mouseCoords.x, &mouseCoords.y);

        SDL_FPoint logicalCoords;
        SDL_RenderCoordinatesFromWindow(this->getRenderer(), mouseCoords.x, mouseCoords.y, &logicalCoords.x, &logicalCoords.y);

        return logicalCoords;
    }

    SDL_Rect BackendRenderer::floatRectToRect(SDL_FRect rect) {
        SDL_Rect int_rect = {
            (int)rect.x,
            (int)rect.y,
            (int)rect.w,
            (int)rect.h
        };
        
        return int_rect;
    }
}