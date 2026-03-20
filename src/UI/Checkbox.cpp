#include "espeon/UI/Checkbox.hpp"

#include <iostream>

namespace espeon {
    Checkbox::Checkbox(Vector2 pos, Vector2 size, CheckboxTextures textures, bool checked) : UIBase(pos, size) {
        this->backendRenderer = BackendRenderer::get();

        this->checkboxTexture = new espeon::Texture(textures.checkboxTexturePath);
        if (!this->checkboxTexture->getTexture()) {
            std::cout << "Could not load checkbox texture: " << SDL_GetError() << std::endl;
        }

        this->checkTexture = new espeon::Texture(textures.checkTexturePath);
        if (!this->checkTexture->getTexture()) {
            std::cout << "Could not load check texture: " << SDL_GetError() << std::endl;
        }

        this->checkboxRect = HoverRect(this->backendRenderer->textureToRect(this->checkboxTexture->getTexture()));
        this->backendRenderer->setRectPos(&this->checkboxRect.rect, pos);
        
        this->rect.rect.w = this->checkboxRect.rect.w;
        this->rect.rect.h = this->checkboxRect.rect.h;
        
        this->checkRect = this->backendRenderer->textureToRect(this->checkTexture->getTexture());
        this->backendRenderer->setRectPos(&this->checkRect, pos);

        this->onClick([this]() {
            this->checkTexture->setVisible(!this->checkTexture->isVisible());
        });
    }

    void Checkbox::draw() {
        auto renderer = this->backendRenderer->getRenderer();
        SDL_FPoint center = {this->checkboxTexture->getTexture()->w / 2.f, this->checkboxTexture->getTexture()->h / 2.f};
    
        if (this->isVisible()) {
            SDL_RenderTextureRotated(renderer, this->checkboxTexture->getTexture(), NULL, &this->checkboxRect.rect, 0.0, &center, SDL_FLIP_NONE);
            if (checkTexture->isVisible()) {
                SDL_RenderTextureRotated(renderer, this->checkTexture->getTexture(), NULL, &this->checkRect, 0.0, &center, SDL_FLIP_NONE);
            }
        }

        UIBase::draw();
    }

    void Checkbox::setLabel(std::string text, TTF_Font* font, SDL_Color color, TextAlign alignment) {
        this->alignment = alignment;

        switch (alignment) {
            case TEXT_ALIGN_RIGHT: {
                this->label = new espeon::Label(
                    {0, 0}, 
                    {static_cast<int>(this->rect.rect.w), static_cast<int>(this->rect.rect.h)}, 
                    text, font, color
                );

                int textWidth, textHeight;
                TTF_GetTextSize(label->getText(), &textWidth, &textHeight);

                auto rect = this->rect.rect;
                label->setPos({
                    static_cast<int>(rect.x + textWidth),
                    static_cast<int>(rect.y + (rect.h - textHeight) / 2.f)
                });

                this->addElement(label);
                break;
            }

            case TEXT_ALIGN_LEFT: {
                this->label = new espeon::Label(
                    {0, 0}, 
                    {static_cast<int>(this->rect.rect.w), static_cast<int>(this->rect.rect.h)}, 
                    text, font, color
                );

                int textWidth, textHeight;
                TTF_GetTextSize(label->getText(), &textWidth, &textHeight);

                auto rect = this->rect.rect;
                label->setPos({
                    static_cast<int>((rect.x - textWidth) - 5.f),
                    static_cast<int>(rect.y + (rect.h - textHeight) / 2.f)
                });

                this->addElement(label);
                break;
            }
        }
    }

    void Checkbox::setPos(Vector2 pos) {
        UIBase::setPos(pos);

        switch (this->alignment) {
            case TEXT_ALIGN_RIGHT: {
                int textWidth, textHeight;
                TTF_GetTextSize(label->getText(), &textWidth, &textHeight);

                auto rect = this->rect.rect;
                this->label->setPos({
                    static_cast<int>(rect.x + textWidth),
                    static_cast<int>(rect.y + (rect.h - textHeight) / 2.f)
                });

                break;
            }

            case TEXT_ALIGN_LEFT: {
                int textWidth, textHeight;
                TTF_GetTextSize(label->getText(), &textWidth, &textHeight);

                auto rect = this->rect.rect;
                label->setPos({
                    static_cast<int>((rect.x - textWidth) - 5.f),
                    static_cast<int>(rect.y + (rect.h - textHeight) / 2.f)
                });
                
                break;
            }
        }
    }
}