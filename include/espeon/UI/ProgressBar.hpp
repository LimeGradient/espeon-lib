#pragma once

#include "espeon/UI/Primitive.hpp"
#include "espeon/UI/UIBase.hpp"

namespace espeon {
    class ProgressBar : public UIBase {
    public:
        struct ProgressBarPrimitive {
            Vector2 size;
            SDL_Color color;
        };

        ProgressBar(Vector2 pos, Vector2 size, ProgressBarPrimitive background, ProgressBarPrimitive progressBar, float minValue, float maxValue, float defaultValue = 0.f);

        void draw() override;

        float getMinValue() {
            return this->minValue;
        }

        void setMinValue(float minValue) {
            this->minValue = minValue;
        }

        float getMaxValue() {
            return this->maxValue;
        }

        void setMaxValue(float maxValue) {
            this->maxValue = maxValue;
        }

        float getValue() {
            return this->value;
        }

        void setValue(float value) {
            if (value <= maxValue) {
                this->value = value;
                this->progressBarPrimitive->rect.getRect()->w = progressBarWidth * (value / maxValue);
                this->c_onValueChanged(value);
            }
        }

        void onValueChanged(std::function<void(float)> callback) {
            this->c_onValueChanged = callback;
        };

    private:
        using UIBase::runOnClick;
        using UIBase::runOnDrag;
        using UIBase::runOnHover;
        using UIBase::runOnHoverEnd;

        float progressBarWidth;

        float minValue;
        float maxValue;
        float value;

        ProgressBarPrimitive background;
        ProgressBarPrimitive progressBar;

        espeon::Primitive* backgroundPrimitive;
        espeon::Primitive* progressBarPrimitive;

        std::function<void(float)> c_onValueChanged;
    };
}