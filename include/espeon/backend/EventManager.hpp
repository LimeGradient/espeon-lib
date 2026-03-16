#pragma once

#include <SDL3/SDL.h>

namespace espeon {
    class EventManager {
    public:
        static EventManager* get() {
            static EventManager instance;
            return &instance;
        }
 
        bool isDragging() {
            return this->dragging;
        }

        void setDragging(bool dragging) {
            this->dragging = dragging;
        }

        SDL_Event* getEvent() {
            return this->event;
        }

        void setEvent(SDL_Event* event) {
            this->event = event;
        }
    private:
        bool dragging = false;
        SDL_Event* event;
    };
}