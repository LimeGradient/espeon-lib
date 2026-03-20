#pragma once

#include <functional>

#include "espeon/backend/BackendRenderer.hpp"
#include "espeon/backend/EventManager.hpp"
#include "espeon/Scene.hpp"

namespace espeon {
    class SceneManager {
    public:
        static SceneManager* get() {
            static SceneManager instance;
            return &instance;
        }

        template <typename T>
        void loadScene(SDL_Renderer* renderer) {
            loadQueuedScene = [this, renderer]() {
                currentScene = T::create(renderer);
            };
            sceneChanged = true;
        }

        template <typename T>
        void loadSceneWithWindow(SDL_Window* window, SDL_Renderer* renderer) {
            loadQueuedScene = [this, window, renderer]() {
                currentScene = T::create(window, renderer);
            };
            sceneChanged = true;
        }

        template <typename T>
        T getScene() {
            return static_cast<T>(this->currentScene);
        }

        void unloadScene() {
            if (currentScene != nullptr) {
                delete currentScene;
                currentScene = nullptr;
            }
        }

        void updateScene() {
            if (sceneChanged) {
                this->unloadScene();
                loadQueuedScene();
                sceneChanged = false;
            }

            currentScene->drawAllElements();
        }

        void updateSceneEvents(SDL_Event* event) {
            if (currentScene != nullptr) {
                auto eventManager = EventManager::get();

                switch (event->type) {
                    case SDL_EVENT_MOUSE_BUTTON_DOWN: {
                        SDL_FPoint click = this->backendRenderer->getLogicalMousePos();
                        eventManager->setDragging(true);
                        currentScene->detectOnClick(click);
                        
                        break;
                    }
                    case SDL_EVENT_MOUSE_BUTTON_UP: {
                        eventManager->setDragging(false);

                        break;
                    }
                    case SDL_EVENT_MOUSE_MOTION: {
                        SDL_FPoint mousePos = this->backendRenderer->getLogicalMousePos();
                        currentScene->detectOnHover(mousePos);

                        if (eventManager->isDragging()) {
                            currentScene->detectOnDrag(mousePos);
                        }

                        break;
                    }
                }

                if (SDL_TextInputActive(this->backendRenderer->getWindow())) {
                    currentScene->detectTyping(event);
                }
            }
        } 

    private:
        bool sceneChanged;
        Scene* currentScene;
        std::function<void()> loadQueuedScene;
        BackendRenderer* backendRenderer = BackendRenderer::get();
    };
}