#pragma once

#include <string>
#include <SDL3/SDL.h>

#include "espeon/types/Vector2.hpp"
#include "espeon/UI/Label.hpp"
#include "espeon/UI/UIBase.hpp"

namespace espeon {
    class Button : public UIBase {
    public:
        Button(Vector2 pos, Vector2 size, SDL_Color fillColor);
        Button(Vector2 pos, Vector2 size, std::string texturePath);
        
        void draw() override;

        void setLabel(std::string text, TTF_Font* font, SDL_Color color);
        void updateLabel(std::string text) {
            this->label->updateText(text);
        }

        bool loadTexture(std::string texturePath);
        void unloadTexture();

        SDL_Texture* getTexture() {
            return this->texture;
        }

        void setTexture(SDL_Texture* texture) {
            this->texture = texture;
        }
    private:
        using UIBase::runOnClick;
        using UIBase::runOnDrag;
        using UIBase::runOnHover;
        using UIBase::runOnHoverEnd;

        SDL_Color fillColor;
        
        std::string texturePath;
        SDL_Texture* texture;
        espeon::Label* label;
    };
}