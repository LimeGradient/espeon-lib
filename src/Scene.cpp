#include "espeon/Scene.hpp"

#include "espeon/UI/TextInput.hpp"
#include "espeon/backend/BackendRenderer.hpp"

namespace espeon {
    bool Scene::setup(SDL_Window* window, SDL_Renderer* renderer) {
        this->renderer = renderer;
        BackendRenderer::get()->setup(window, renderer);

        return this->init();
    }

    void Scene::addElement(UIBase* element) {
        this->elements.push_back(std::unique_ptr<UIBase>(element));
    }

    void Scene::drawAllElements() {
        for (auto& element : elements) {
            element->draw();
        }
        SDL_RenderPresent(this->renderer);
        SDL_RenderClear(this->renderer);
    }

    void Scene::detectOnClick(SDL_FPoint click) {
        for (auto& element : this->elements) {
            if (element->passthrough) {
                element->detectOnClick(click);
            }

            if (SDL_PointInRectFloat(&click, element->rect.getRect())) {
                element->runOnClick();
            }
        }
    }

    void Scene::detectOnHover(SDL_FPoint coords) {
        bool wasHovering = false;
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

    void Scene::detectOnDrag(SDL_FPoint mouseCoords) {
        for (auto& element : this->elements) {
            if (element->passthrough) {
                element->detectOnDrag(mouseCoords);
            } else {
                if (SDL_PointInRectFloat(&mouseCoords, element->rect.getRect())) {
                    element->runOnDrag();
                }
            }
        }
    }

    void Scene::detectTyping(SDL_Event* event) {
        for (auto& element : this->elements) {
            if (auto input = dynamic_cast<TextInput*>(element.get())) {
                if (input->getFocused()) {
                    input->handleEvents(event);
                }
            }
        }
    }
}