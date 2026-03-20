#include "espeon/UI/TextInput.hpp"

namespace espeon {
    TextInput::TextInput(Vector2 pos, Vector2 size, TTF_Font* font, SDL_Color placeholderColor, std::string placeholder) : UIBase(pos, size) {
        this->backendRenderer = BackendRenderer::get();
        this->eventManager = EventManager::get();
        this->window = this->backendRenderer->getWindow();

        this->inputText = new espeon::Label(
            {0, 0}, 
            {static_cast<int>(this->rect.getRect()->w), static_cast<int>(this->rect.getRect()->h)}, 
            placeholder, font, placeholderColor
        );

        int textWidth, textHeight;
        TTF_GetTextSize(inputText->getText(), &textWidth, &textHeight);

        auto rect = *this->rect.getRect();
        this->inputText->setPos({
            static_cast<int>(rect.x),
            static_cast<int>(rect.y + (rect.h - textHeight) / 2.f)
        });

        this->addElement(this->inputText);

        this->onClick([this]() {
            auto window = this->backendRenderer->getWindow();

            SDL_Rect area = this->backendRenderer->floatRectToRect(*this->rect.getRect());
            SDL_SetTextInputArea(
                window, 
                &area,
                cursor
            );
            SDL_StartTextInput(window);

            this->focused = true;
        });
    }

    void TextInput::handleEvents(SDL_Event* event) {
        switch (event->type) {
            case SDL_EVENT_TEXT_INPUT: {
                if (std::strlen(this->text) <= this->textLimit) {
                    SDL_strlcat(text, event->text.text, sizeof(text));
                    this->inputText->updateText(std::string(this->text));

                    break;
                }
            }
            
            case SDL_EVENT_KEY_DOWN: {
                if (event->key.key == SDLK_ESCAPE || event->key.key == SDLK_RETURN) {
                    SDL_StopTextInput(window);
                    textInputComplete = true;
                    this->focused = false;
                } else if (event->key.key == SDLK_BACKSPACE) {
                    auto textLen = std::strlen(this->text);
                    this->text[textLen - 1] = '\0';
                    this->inputText->updateText(std::string(this->text));
                }

                break;
            }
        }
    }

    void TextInput::draw() {
        SDL_RenderFillRect(this->backendRenderer->getRenderer(), this->rect.getRect());

        UIBase::draw();
    }

    void TextInput::setLabel(std::string text, TTF_Font* font, SDL_Color color) {
        this->label = new espeon::Label(
            {0, 0}, 
            {static_cast<int>(this->rect.rect.w), static_cast<int>(this->rect.rect.h)}, 
            text, font, color
        );

        int textWidth, textHeight;
        TTF_GetTextSize(label->getText(), &textWidth, &textHeight);

        auto rect = this->rect.rect;
        this->label->setPos({
            static_cast<int>(rect.x),
            static_cast<int>(rect.y - (rect.h - textHeight))
        });

        this->addElement(this->label);
    }

    void TextInput::setPos(Vector2 pos) {
        UIBase::setPos(pos);

        int textWidth, textHeight;
        TTF_GetTextSize(label->getText(), &textWidth, &textHeight);

        auto rect = this->rect.rect;
        this->label->setPos({
            static_cast<int>(rect.x),
            static_cast<int>(rect.y - (rect.h - textHeight))
        });
    }
}