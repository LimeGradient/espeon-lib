#include "espeon/UI/Layout.hpp"

namespace espeon {
    Layout::Layout(Vector2 pos, Vector2 size, LayoutDirection direction, LayoutAlign align, float spacing) : UIBase(pos, size) {
        this->passthrough = true;

        this->pos = pos;
        this->size = size;
        this->backendRenderer = BackendRenderer::get();
        this->rect = HoverRect();

        this->direction = direction;
        this->align = align;
        this->spacing = spacing;
    }

    void Layout::updateLayout() {
        switch (this->direction) {
            case ROW: {
                switch (this->align) {
                    case LEFT: {
                        Vector2 lastPos = {0, 0};
                        for (auto& element : elements) {
                            Vector2 currentPos = element->pos;
                            if (lastPos.x == 0 && lastPos.y == 0) {
                                currentPos.x = this->pos.x;
                                currentPos.y = (this->size.y / 2);
                            } else {
                                currentPos.x = lastPos.x + this->spacing;
                                currentPos.y = lastPos.y;
                            }
                            element->setPos(currentPos);
                            lastPos = currentPos;
                        }
                        break;
                    }
                    case RIGHT: {
                        Vector2 lastPos = {0, 0};
                        for (auto& element : elements) {
                            Vector2 currentPos = element->pos;
                            if (lastPos.x == 0 && lastPos.y == 0) {
                                currentPos.x = this->size.x + this->pos.x;
                                currentPos.y = (this->size.y / 2);
                            } else {
                                currentPos.x = lastPos.x + this->spacing;
                                currentPos.y = lastPos.y;
                            }
                            element->setPos(currentPos);
                            lastPos = currentPos;
                        }
                        break;
                    }
                    case CENTER: {
                        Vector2 lastPos = {0, 0};
                        for (auto& element : elements) {
                            Vector2 currentPos = element->pos;
                            if (lastPos.x == 0 && lastPos.y == 0) {
                                currentPos.x = (this->size.x / 2) + this->pos.x;
                                currentPos.y = this->size.y / 2;
                            } else {
                                currentPos.x = lastPos.x + this->spacing;
                                currentPos.y = lastPos.y;
                            }
                            element->setPos(currentPos);
                            lastPos = currentPos;
                        }
                        break;
                    }
                }
                break;
            }
            case COLUMN: {
                switch (this->align) {
                    case LEFT: {
                        Vector2 lastPos = {0, 0};
                        for (auto& element : elements) {
                            Vector2 currentPos = element->pos;
                            if (lastPos.x == 0 && lastPos.y == 0) {
                                currentPos.x = this->pos.x;
                                currentPos.y = (this->size.y / 2);
                            } else {
                                currentPos.x = lastPos.x;
                                currentPos.y = lastPos.y + this->spacing;
                            }
                            element->setPos(currentPos);
                            lastPos = currentPos;
                        }
                        break;
                    }
                    case RIGHT: {
                        Vector2 lastPos = {0, 0};
                        for (auto& element : elements) {
                            Vector2 currentPos = element->pos;
                            if (lastPos.x == 0 && lastPos.y == 0) {
                                currentPos.x = this->size.x + this->pos.x;
                                currentPos.y = (this->size.y / 2);
                            } else {
                                currentPos.x = lastPos.x;
                                currentPos.y = lastPos.y + this->spacing;
                            }
                            element->setPos(currentPos);
                            lastPos = currentPos;
                        }
                        break;
                    }
                    case CENTER: {
                        Vector2 lastPos = {0, 0};
                        for (auto& element : elements) {
                            Vector2 currentPos = element->pos;
                            if (lastPos.x == 0 && lastPos.y == 0) {
                                currentPos.x = (this->pos.x + ((this->size.x - element->getSize().x) / 2));
                                currentPos.y = (this->size.y / 2) - (element->getSize().y / 2);
                            } else {
                                currentPos.x = lastPos.x;
                                currentPos.y = lastPos.y + this->spacing;
                            }
                            SDL_Log("current pos - X: %d | Y: %d", currentPos.x, currentPos.y);
                            element->setPos(currentPos);
                            lastPos = currentPos;
                        }
                        break;
                    }
                }
                break;
            }
        }
    }
}