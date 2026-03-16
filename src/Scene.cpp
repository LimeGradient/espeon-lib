#include "espeon/Scene.hpp"

#include "espeon/UI/TextInput.hpp"
#include "espeon/backend/BackendRenderer.hpp"

namespace espeon {
    bool Scene::setup(SDL_Window* window, SDL_Renderer* renderer) {
        this->backendRenderer = BackendRenderer::get();
        this->backendRenderer->setup(window, renderer);

        return this->init();
    }

    void Scene::addElement(UIBase* element) {
        this->elements.push_back(std::unique_ptr<UIBase>(element));
    }

    void Scene::drawAllElements() {
        SDL_SetRenderDrawColor(this->backendRenderer->getRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(this->backendRenderer->getRenderer());
        for (auto& element : elements) {
            element->draw();
        }
        SDL_RenderPresent(this->backendRenderer->getRenderer());
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