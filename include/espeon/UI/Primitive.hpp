#pragma once

#include "espeon/backend/BackendRenderer.hpp"
#include "espeon/UI/UIBase.hpp"

namespace espeon {
    class Primitive : public UIBase {
    public:
        Primitive(Vector2 pos, Vector2 size, SDL_Color fillColor);

        void draw() override;

        void setOutline(SDL_Color color, float thickness);

    private:
        BackendRenderer* backendRenderer;

        SDL_Color fillColor;

        SDL_FRect outlineRect;
        SDL_Color outlineColor = {};
        float outlineThickness;
    };
}