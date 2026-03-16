#pragma once

#include <string>

#include "espeon/backend/BackendRenderer.hpp"
#include "espeon/backend/EventManager.hpp"
#include "espeon/UI/Label.hpp"
#include "espeon/UI/UIBase.hpp"

namespace espeon {
    class TextInput : public UIBase {
    public:
        TextInput(Vector2 pos, Vector2 size, TTF_Font* font, SDL_Color placeholderColor, std::string placeholder);

        void draw() override;
        void handleEvents(SDL_Event* event);

        void setLabel(std::string text, TTF_Font* font, SDL_Color color);
        void updateLabel(std::string text) {
            this->label->updateText(text);
        }

        int getCharacterLimit() {
            return this->textLimit;
        }

        void setCharacterLimit(int limit) {
            this->textLimit = limit;
        }

        bool getFocused() {
            return this->focused;
        }

    private:
        using UIBase::runOnClick;
        using UIBase::runOnDrag;
        using UIBase::runOnHover;
        using UIBase::runOnHoverEnd;

        BackendRenderer* backendRenderer;
        EventManager* eventManager;
        SDL_Window* window;

        TTF_Font* font;
        SDL_Color placeholderColor;
        espeon::Label* label;
        espeon::Label* inputText;

        bool focused = false;
        char text[1024] = { 0 };
        int textLimit = 1024;
        bool textInputComplete = false;
        int cursor = 0;
    };
}