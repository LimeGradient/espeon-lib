#include "espeon/UI/Button.hpp"

#include <iostream>

#include <SDL3_image/SDL_image.h>

namespace espeon {
    Button::Button(Vector2 pos, Vector2 size, SDL_Color fillColor) : UIBase(pos, size) {
        this->fillColor = fillColor;
        this->backendRenderer = BackendRenderer::get();
        this->drawType = EDrawType::ESPEON_DRAW_FILLED;
    }

    Button::Button(Vector2 pos, Vector2 size, std::string texturePath) : UIBase(pos, size) {
        this->texturePath = texturePath;
        this->backendRenderer = BackendRenderer::get();

        this->texture = IMG_LoadTexture(this->backendRenderer->getRenderer(), texturePath.c_str());
        if (!this->texture) {
            std::cout << "Failed to load texture: " << SDL_GetError() << std::endl;
        }

        this->drawType = EDrawType::ESPEON_DRAW_TEXTURE;
    }

    void Button::draw() {
        switch (this->drawType) {
            case ESPEON_DRAW_FILLED: {
                auto renderer = this->backendRenderer->getRenderer();
                SDL_SetRenderDrawColor(renderer, this->fillColor.r, this->fillColor.g, this->fillColor.b, this->fillColor.a);
                SDL_RenderFillRect(renderer, &this->rect.rect);
                break;
            }
            case ESPEON_DRAW_TEXTURE: {
                auto renderer = this->backendRenderer->getRenderer();
                SDL_FPoint center = {this->texture->w / 2.f, this->texture->h / 2.f};
                SDL_RenderTextureRotated(renderer, this->texture, NULL, &this->rect.rect, 0.0, &center, SDL_FLIP_NONE);
                break;
            }
        }

        UIBase::draw();
    }

    void Button::setLabel(std::string text, TTF_Font* font, SDL_Color color) {
        this->label = new espeon::Label(
            {0, 0}, 
            {static_cast<int>(this->rect.rect.w), static_cast<int>(this->rect.rect.h)}, 
            text, font, color
        );

        int textWidth, textHeight;
        TTF_GetTextSize(label->getText(), &textWidth, &textHeight);

        auto rect = this->rect.rect;
        label->setPos({
            static_cast<int>(rect.x + (rect.w - textWidth) / 2.f),
            static_cast<int>(rect.y + (rect.h - textHeight) / 2.f)
        });

        this->addElement(label);
    }

    bool Button::loadTexture(std::string texturePath) {
        this->unloadTexture();

        this->texture = this->backendRenderer->loadImage(texturePath);
        if (!this->texture) {
            return false;
        }

        return true;
    }

    void Button::unloadTexture() {
        SDL_DestroyTexture(this->texture);
        this->texture = nullptr;
    }

    void Button::setPos(Vector2 pos) {
        UIBase::setPos(pos);

        int textWidth, textHeight;
        TTF_GetTextSize(label->getText(), &textWidth, &textHeight);

        auto rect = this->rect.rect;
        this->label->setPos({
            static_cast<int>(rect.x + (rect.w - textWidth) / 2.f),
            static_cast<int>(rect.y + (rect.h - textHeight) / 2.f)
        });
    }
}