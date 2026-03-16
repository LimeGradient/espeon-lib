#include "espeon/UI/Primitive.hpp"

namespace espeon {
    Primitive::Primitive(Vector2 pos, Vector2 size, SDL_Color fillColor) : UIBase(pos, size) {
        this->passthrough = true;
        this->backendRenderer = BackendRenderer::get();
        
        this->fillColor = fillColor;
    }

    void Primitive::draw() {
        auto renderer = this->backendRenderer->getRenderer();

        if (outlineColor.a != 0) {
            SDL_SetRenderDrawColor(renderer, outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a);
            this->outlineRect = {
                static_cast<float>(pos.x),
                static_cast<float>(pos.y),
                size.x * this->outlineThickness,
                size.y * this->outlineThickness,
            };
            SDL_RenderFillRect(renderer, &this->outlineRect);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        }

        auto rect = this->rect.getRect();
        SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
        SDL_RenderFillRect(renderer, rect);

        UIBase::draw();
    }
}