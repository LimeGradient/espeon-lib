#include "LCETitle.hpp"

#include <iostream>

bool LCETitleScreen::init() {
    auto window = this->backendRenderer->getWindow();

    int winWidth, winHeight;
    SDL_GetWindowSize(window, &winWidth, &winHeight);

    auto background = new espeon::Primitive(
        {winWidth / 2, winHeight / 2}, {700, 300}, {255, 0, 255, SDL_ALPHA_OPAQUE}
    );

    background->setPos({
        (winWidth / 2) - (background->getSize().x / 2),
        (winHeight / 2) - (background->getSize().y / 2)
    });

    this->addElement(background);

    auto rect = background->getRect();
    auto center = this->backendRenderer->getCenter(&rect);

    auto layout = new espeon::Layout(
        {(int)center.x, (int)center.y}, {500, 700}, espeon::Layout::LayoutDirection::COLUMN, espeon::Layout::LayoutAlign::CENTER, 60.f
    );

    background->addElement(layout);

    auto font = espeon::Label::loadFont("./Common/res/font/mojangles.otf", 16);

    for (int i = 0; i < 5; i++) {
        auto button = new MinecraftButton(
            {winWidth / 2, winHeight / 2}, {400, 50}, "./Common/Media/Graphics/MainMenuButton_Norm.png"
        );

        button->onClick([button]() {
            std::cout << "i was just clicked!" << std::endl;
            button->setPos({button->getPos().x, button->getPos().y + 10});
        });

        button->onHover([button]() {
            std::cout << "Hover Start" << std::endl;
            button->loadTexture("./Common/Media/Graphics/MainMenuButton_Over.png");
        });

        button->onHoverEnd([button]() {
            std::cout << "Hover End" << std::endl;
            button->loadTexture("./Common/Media/Graphics/MainMenuButton_Norm.png");
        });

        button->setLabel("Minecraft", font, {255, 255, 255, SDL_ALPHA_OPAQUE});

        layout->addElement(button);
    }

    layout->updateLayout();

    return true;
}