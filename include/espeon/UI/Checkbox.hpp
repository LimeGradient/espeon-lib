#pragma once

#include <string>
#include <functional>

#include "espeon/types/Texture.hpp"
#include "espeon/UI/Label.hpp"
#include "espeon/UI/UIBase.hpp"

namespace espeon {
    class Checkbox : public UIBase {
    public:
        struct CheckboxTextures {
            std::string checkboxTexturePath;
            std::string checkTexturePath;
        };

        enum TextAlign {
            TEXT_ALIGN_LEFT,
            TEXT_ALIGN_RIGHT
        };

        Checkbox(Vector2 pos, Vector2 size, CheckboxTextures textures, bool checked = false);

        void draw() override;

        void onChecked(std::function<void(bool)> callback) {
            this->c_onChecked = callback;
        };

        espeon::Label* getLabel() {
            return this->label;
        }
        void setLabel(std::string text, TTF_Font* font, SDL_Color color, TextAlign align);
        void updateLabel(std::string text) {
            this->label->updateText(text);
        }

        void setPos(Vector2 pos) override;

        bool isChecked() {
            return this->checked;
        }

        void setChecked(bool checked) {
            this->checked = checked;
        }
    private:
        using UIBase::runOnClick;
        using UIBase::runOnDrag;
        using UIBase::runOnHover;
        using UIBase::runOnHoverEnd;

        std::function<void(bool)> c_onChecked;

        espeon::Texture* checkboxTexture;
        espeon::Texture* checkTexture;
        HoverRect checkboxRect;
        SDL_FRect checkRect;
        bool checked = false;
        espeon::Label* label;
        TextAlign alignment;
    };
}