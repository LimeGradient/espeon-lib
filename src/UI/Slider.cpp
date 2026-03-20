#include "espeon/UI/Slider.hpp"

#include <iostream>

#include <SDL3_image/SDL_image.h>

#include "espeon/backend/EventManager.hpp"
#include "espeon/UI/Label.hpp"

namespace espeon {
    Slider::Slider(Vector2 pos, Vector2 size, float minValue, float maxValue, Slider::SliderTextures texturesPath, float defaultValue) : UIBase(pos, size) {
        this->backendRenderer = BackendRenderer::get();

        this->trackRect = this->rect.rect;

        this->minValue = minValue;
        this->maxValue = maxValue;
        this->value = defaultValue;
        this->texturesPath = texturesPath;

        this->trackTexture = this->backendRenderer->loadImage(texturesPath.trackTexturePath);
        if (!this->trackTexture) {
            std::cout << "Failed to load texture: " << SDL_GetError() << std::endl;
        }

        this->buttonTexture = this->backendRenderer->loadImage(texturesPath.buttonTexturePath);
        if (!this->buttonTexture) {
            std::cout << "Failed to load texture: " << SDL_GetError() << std::endl;
        }

        this->buttonRect = SDL_FRect {
            static_cast<float>(pos.x),
            static_cast<float>(pos.y),
            static_cast<float>(buttonTexture->w),
            static_cast<float>(size.y)
        };

        this->onClick([this, minValue, maxValue]() mutable {
            SDL_FPoint mousePos = this->backendRenderer->getLogicalMousePos();

            this->buttonRect.rect.x = mousePos.x;
            
            this->value = SDL_clamp((buttonRect.rect.x - trackRect.x) / trackRect.w, minValue, maxValue);

            this->c_onValueChanged(this->value);
        });

        auto eventManager = EventManager::get();
        this->onDrag([this, minValue, maxValue, eventManager]() {
            if (eventManager->isDragging()) {
                std::cout << "dragging" << std::endl;
            }

            SDL_FPoint mousePos = this->backendRenderer->getLogicalMousePos();

            this->buttonRect.rect.x = mousePos.x;
            
            this->value = SDL_clamp((buttonRect.rect.x - trackRect.x) / trackRect.w, minValue, maxValue);

            this->c_onValueChanged(this->value);
        });
    }

    void Slider::draw() {
        auto renderer = this->backendRenderer->getRenderer();
        SDL_FPoint center = {this->trackTexture->w / 2.f, this->trackTexture->h / 2.f};

        SDL_RenderTextureRotated(renderer, this->trackTexture, NULL, &this->trackRect, 0.0, &center, SDL_FLIP_NONE);
        SDL_RenderTextureRotated(renderer, this->buttonTexture, NULL, &this->buttonRect.rect, 0.0, &center, SDL_FLIP_NONE);

        UIBase::draw();
    };

    void Slider::setLabel(std::string text, TTF_Font* font, SDL_Color color) {
        this->label = new espeon::Label(
            {0, 0}, 
            {static_cast<int>(this->rect.rect.w), static_cast<int>(this->rect.rect.h)}, 
            text, font, color
        );

        int textWidth, textHeight;
        TTF_GetTextSize(label->getText(), &textWidth, &textHeight);

        auto rect = this->rect.rect;
        this->label->setPos({
            static_cast<int>(rect.x + (rect.w - textWidth) / 2.f),
            static_cast<int>(rect.y + (rect.h - textHeight) / 2.f)
        });

        this->addElement(this->label);
    }

    void Slider::setPos(Vector2 pos) {
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