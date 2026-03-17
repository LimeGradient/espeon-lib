#pragma once

#include <string>

#include <SDL3_ttf/SDL_ttf.h>

#include "espeon/types/Vector2.hpp"
#include "espeon/UI/UIBase.hpp"

namespace espeon {
    class Label : public UIBase {
    public:
        Label(Vector2 pos, Vector2 size, std::string text, TTF_Font* font, SDL_Color color);
        static SDL_Texture* createRawLabel(std::string text, TTF_Font* font, SDL_Color color);

        void draw() override;
        static TTF_Font* loadFont(std::string path, int fontSize);

        void updateText(std::string text) {
            TTF_SetTextString(this->text, text.c_str(), text.length());
        }

        TTF_Text* getText() {
            return this->text;
        }
        void setText(TTF_Text* text) {
            this->text = text;
        }

        void setTextColor(SDL_Color color) {
            TTF_SetTextColor(this->text, color.r, color.g, color.b, color.a);
        }

        Vector2 getTextSize();

    private:
        using UIBase::runOnClick;
        using UIBase::runOnDrag;
        using UIBase::runOnHover;
        using UIBase::runOnHoverEnd;

        TTF_TextEngine* textEngine;
        TTF_Text* text;
        TTF_Font* font;
    };
}