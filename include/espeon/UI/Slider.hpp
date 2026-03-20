#pragma once

#include <functional>
#include <string>
#include <SDL3/SDL.h>

#include "espeon/UI/Label.hpp"
#include "espeon/UI/UIBase.hpp"

namespace espeon {
    class Slider : public UIBase {
    public:
        struct SliderTextures {
            std::string trackTexturePath;
            std::string buttonTexturePath;
        };

        Slider(Vector2 pos, Vector2 size, float minValue, float maxValue, SliderTextures texturesPath, float defaultValue = 0.f);

        void onValueChanged(std::function<void(float)> callback) {
            this->c_onValueChanged = callback;
        };

        void draw() override;

        espeon::Label* getLabel() {
            return this->label;
        }
        void setLabel(std::string text, TTF_Font* font, SDL_Color color);
        void updateLabel(std::string text) {
            this->label->updateText(text);
        }

        void setPos(Vector2 pos) override;

        float getValue() {
            return this->value;
        }
    private:
        using UIBase::runOnClick;
        using UIBase::runOnDrag;
        using UIBase::runOnHover;
        using UIBase::runOnHoverEnd;

        SDL_FRect trackRect;
        HoverRect buttonRect;
        espeon::Label* label;
        SliderTextures texturesPath;
        float minValue;
        float maxValue;
        float value;
        SDL_Texture* trackTexture;
        SDL_Texture* buttonTexture;



        std::function<void(float)> c_onValueChanged = std::function<void(float)>();
    };
}