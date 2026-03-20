#pragma once

#include <espeon/Scene.hpp>
#include <espeon/UI/UI.hpp>

class MinecraftButton : public espeon::Button {
public:
    MinecraftButton(espeon::Vector2 pos, espeon::Vector2 size, std::string texturePath) : espeon::Button(pos, size, texturePath) {}

    void setLabel(std::string text, TTF_Font* font, SDL_Color color) {
        this->labelShading = new espeon::Label(
            {0, 0}, 
            {static_cast<int>(this->rect.rect.w), static_cast<int>(this->rect.rect.h)}, 
            text, font, {0, 0, 0, SDL_ALPHA_OPAQUE}
        );

        this->labelShading->setTextColor({0, 0, 0, 255});

        auto textSize = this->labelShading->getTextSize();

        auto rect = this->rect.rect;

        this->labelShading->setPos({
            static_cast<int>(rect.x + (rect.w - textSize.x) / 2.f) + 1,
            static_cast<int>(rect.y + (rect.h - textSize.y) / 2.f) + 1
        });

        this->addElement(this->labelShading);

        espeon::Button::setLabel(text, font, color);
    }

    void setPos(espeon::Vector2 pos) override {
        espeon::Button::setPos(pos);

        int textWidth, textHeight;
        TTF_GetTextSize(this->labelShading->getText(), &textWidth, &textHeight);

        auto rect = this->rect.rect;
        this->labelShading->setPos({
            this->getLabel()->getPos().x + 1,
            this->getLabel()->getPos().y + +1
        });
    }

private:
    espeon::Label* labelShading;
};

class LCETitleScreen : public espeon::Scene {
private:
    bool init() override;

public:
    static LCETitleScreen* create(SDL_Window* window, SDL_Renderer* renderer) {
        auto* ret = new LCETitleScreen();
        if (!ret->setup(window, renderer)) {
            return nullptr;
        }
        
        return ret;
    }
};