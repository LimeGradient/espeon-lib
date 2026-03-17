#pragma once

#include <string>

#include "espeon/UI/UIBase.hpp"

namespace espeon {
    class Image : public UIBase {
    public:
        Image(Vector2 pos, Vector2 size, std::string imagePath);

        void draw() override;

        bool loadTexture(std::string texturePath);
        void unloadTexture();
    
    private:
        using UIBase::runOnClick;
        using UIBase::runOnDrag;
        using UIBase::runOnHover;
        using UIBase::runOnHoverEnd;

        SDL_Texture* texture;
    };
}