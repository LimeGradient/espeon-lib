#include "espeon/UI/ProgressBar.hpp"

namespace espeon {
    ProgressBar::ProgressBar(
        Vector2 pos, Vector2 size, 
        ProgressBarPrimitive background, ProgressBarPrimitive progressBar, 
        float minValue, float maxValue, float defaultValue
    ) : UIBase(pos, size) {
        this->backendRenderer = BackendRenderer::get();

        this->background = background;
        this->backgroundPrimitive = new espeon::Primitive(
            pos, background.size, background.color
        );
        this->addElement(backgroundPrimitive);

        this->progressBar = progressBar;
        this->progressBarPrimitive = new espeon::Primitive(
            {pos.x + 10, pos.y + 10}, progressBar.size, progressBar.color
        );
        this->addElement(progressBarPrimitive);

        this->progressBarWidth = progressBarPrimitive->getRect().w;
        
        this->minValue = minValue;
        this->maxValue = maxValue;
        this->value = defaultValue;
    }

    void ProgressBar::draw() {
        UIBase::draw();
    }
}