#pragma once

#include <memory>
#include <vector>

#include <SDL3/SDL.h>

#include "espeon/backend/BackendRenderer.hpp"
#include "espeon/UI/UIBase.hpp"

namespace espeon {
    class Scene {
    public:
        template <class CustomScene>
        static CustomScene* create(SDL_Renderer* renderer) {
            CustomScene::create();
        }

        bool setup(SDL_Window* window, SDL_Renderer* renderer);
        void addElement(UIBase* element);
        void drawAllElements();
        void resizeAllElements(int winWidth, int winHeight);

        void detectOnClick(SDL_FPoint click);
        void detectOnHover(SDL_FPoint coords);
        void detectOnDrag(SDL_FPoint mouseCoords);
        void detectTyping(SDL_Event* event);
        
    private:
        virtual bool init() {
            return false;
        }
        
        BackendRenderer* backendRenderer;
        std::vector<std::unique_ptr<UIBase>> elements = {};
    };
}