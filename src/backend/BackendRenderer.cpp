#include "espeon/backend/BackendRenderer.hpp"

namespace espeon {
#if USE_SDL3
    void BackendRenderer::createContext(SDL_Window* window, SDL_Renderer* renderer) {
        this->sdlBackend = SDL3Backend::get();
        this->sdlBackend->createContext(window, renderer);
    }

    void BackendRenderer::drawRectangle(Vector2 pos, Vector2 size, Color fillColor) {
        this->sdlBackend->drawRectangle(pos, size, this->sdlBackend->colorToSDLColor(fillColor));
    }
#endif
}