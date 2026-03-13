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
}