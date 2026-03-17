#pragma once

#include "espeon/types/Vector2.hpp"
#include "espeon/UI/UIBase.hpp"

namespace espeon {
    class Layout : public UIBase {
    public:
        enum LayoutDirection {
            ROW,
            COLUMN
        };

        enum LayoutAlign {
            LEFT,
            RIGHT,
            CENTER
        };

        Layout(Vector2 pos, Vector2 size, LayoutDirection direction, LayoutAlign align, float spacing = 40.f);

        void updateLayout();

        Layout::LayoutDirection getDirection() {
            return this->direction;
        }

        void setDirection(LayoutDirection direction) {
            this->direction = direction;
        }

        LayoutAlign getAlignment() {
            return this->align;
        }

        void setAlignment(LayoutAlign align) {
            this->align = align;
        }

        float getSpacing() {
            return this->spacing;
        }

        void setSpacing(float spacing) {
            this->spacing = spacing;
        }

    private:
        using UIBase::runOnClick;
        using UIBase::runOnDrag;
        using UIBase::runOnHover;
        using UIBase::runOnHoverEnd;

        LayoutDirection direction;
        LayoutAlign align;
        float spacing;
    };
}