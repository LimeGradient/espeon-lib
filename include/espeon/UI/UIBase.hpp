#pragma once

#include <functional>
#include <memory>
#include <vector>

#include <SDL3/SDL_rect.h>

#include "espeon/backend/BackendRenderer.hpp"
#include "espeon/types/EDrawType.hpp"
#include "espeon/types/HoverRect.hpp"
#include "espeon/types/Vector2.hpp"

namespace espeon {
    class UIBase {
    public:
        UIBase(Vector2 pos, Vector2 size) {
            this->setDefaultCallbacks();
            this->pos = pos;
            this->size = size;

            SDL_FRect rect;
            rect.x = pos.x;
            rect.y = pos.y;
            rect.w = size.x;
            rect.h = size.y;
            this->rect = HoverRect(rect);
        }

        virtual ~UIBase() = default;
        virtual void draw() {
            this->drawAllElements();
        };

        void addElement(UIBase* element) {
            this->elements.push_back(std::unique_ptr<UIBase>(element));
        }
        void drawAllElements() {
            if (!elements.empty()) {
                for (auto& element : elements) {
                    element->draw();
                }
            }
        }

        SDL_FRect getRect() {
            return this->rect.rect;
        }
        void setRect(SDL_FRect rect) {
            this->rect = rect;
        }

        void setDefaultCallbacks() {
            this->onClick([]() {
            
            });

            this->onHover([]() {

            });

            this->onHoverEnd([]() {

            });
            this->onDrag([]() {

            });
        }

        void onClick(std::function<void()> callback) {
            this->c_onClick = callback;
        }

        void onHover(std::function<void()> callback) {
            this->c_onHover = callback;
        }

        void onHoverEnd(std::function<void()> callback) {
            this->c_onHoverEnd = callback;
        }

        void onDrag(std::function<void()> callback) {
            this->c_onDrag = callback;
        }

        void runOnClick() {
            this->c_onClick();
        }

        void runOnHover() {
            this->c_onHover();
        }

        void runOnHoverEnd() {
            this->c_onHoverEnd();
        }

        void runOnDrag() {
            this->c_onDrag();
        }

        void detectOnClick(SDL_FPoint click) {
            for (auto& element : this->elements) {
                if (element->passthrough) {
                    element->detectOnClick(click);
                }
                
                if (SDL_PointInRectFloat(&click, element->rect.getRect())) {
                    element->runOnClick();
                }
            }
        }

        void detectOnHover(SDL_FPoint coords) {
            if (!this->elements.empty()) {
                for (auto& element : this->elements) {
                    if (element->passthrough) {
                        element->detectOnHover(coords);
                    }

                    if (element->rect.update(coords)) {
                        if (element->rect.justEntered()) {
                            element->runOnHover();
                        } else {
                            element->runOnHoverEnd();
                        }
                    }
                }
            }
        }

        void detectOnDrag(SDL_FPoint mousePos) {
            for (auto& element : this->elements) {
                if (element->passthrough) {
                    element->detectOnDrag(mousePos);
                } else {
                    if (SDL_PointInRectFloat(&mousePos, &element->rect.rect)) {
                        element->runOnDrag();
                    }
                }
            }
        }

        Vector2 getPos() {
            return this->pos;
        }

        void setPos(Vector2 pos) {
            this->pos = pos;
        }

        Vector2 getSize() {
            return this->size;
        }

        void setSize(Vector2 size) {
            this->size = size;
        }

        bool isVisible() {
            return this->visible;
        }

        void setVisible(bool visible) {
            this->visible = visible;
        }
    
        HoverRect rect;
        EDrawType drawType;
        bool passthrough = false;
        std::vector<std::unique_ptr<UIBase>> elements = {};
        Vector2 pos;
        Vector2 size;

    protected:
        BackendRenderer* backendRenderer;

    private:
        bool wasHovering = false;
        bool visible = true;
        std::function<void()> c_onClick = std::function<void()>();
        std::function<void()> c_onHover = std::function<void()>();
        std::function<void()> c_onHoverEnd = std::function<void()>();
        std::function<void()> c_onDrag = std::function<void()>();
    };
}