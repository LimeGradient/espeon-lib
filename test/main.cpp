#include <iostream>
#include <format>

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <espeon/backend/BackendRenderer.hpp>
#include <espeon/backend/EventManager.hpp>
#include <espeon/Scene.hpp>
#include <espeon/SceneManager.hpp>
#include <espeon/UI/UI.hpp>

#include "LCETitle.hpp"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

class CustomScene : public espeon::Scene {
    bool init() override {
        auto layout = new espeon::Layout(
            {300, 300}, {500, 500}, espeon::Layout::LayoutDirection::ROW, espeon::Layout::LayoutAlign::LEFT
        );
        this->addElement(layout);

        auto button = new MinecraftButton(
            {100, 100}, {500, 50}, "./Common/Media/Graphics/MainMenuButton_Norm.png"
        );

        button->onClick([button]() {
            std::cout << "i was just clicked!" << std::endl;
        });

        button->onHover([button]() {
            std::cout << "Hover Start" << std::endl;
            button->loadTexture("./Common/Media/Graphics/MainMenuButton_Over.png");
        });

        button->onHoverEnd([button]() {
            std::cout << "Hover End" << std::endl;
            button->loadTexture("./Common/Media/Graphics/MainMenuButton_Norm.png");
        });
        auto font = espeon::Label::loadFont("./Common/res/font/mojangles.otf", 16);

        button->setLabel("Minecraft", font, {255, 255, 255, SDL_ALPHA_OPAQUE});

        layout->addElement(button);

        for (int i = 0; i < 10; i++) {
            layout->addElement(new espeon::Label(
                {0, 0}, {250, 50}, "test", font, {255, 255, 255, SDL_ALPHA_OPAQUE}
            ));
        }

        layout->updateLayout();

        auto slider = new espeon::Slider(
            {500, 500}, {500, 50}, 0, 1, {
                "./Common/Media/Graphics/Slider_Track.png",
                "./Common/Media/Graphics/Slider_Button.png"
            }
        );

        slider->setLabel(std::format("FOV: {}", slider->getValue()), font, {255, 255, 255, SDL_ALPHA_OPAQUE});

        slider->onValueChanged([=](float value) {
            std::cout << value << std::endl;
            slider->updateLabel(std::format("FOV: {}", std::to_string((int)(value * 100))));
        });

        this->addElement(slider);

        auto image = new espeon::Image(
            {700, 700}, {100, 100}, "./Common/Media/Graphics/MainMenuButton_Norm.png"
        );

        this->addElement(image);

        auto checkbox = new espeon::Checkbox(
            {700, 300}, {100, 100}, {
                "./Common/Media/Graphics/Tickbox_Norm.png",
                "./Common/Media/Graphics/Tick.png"
            }
        );

        checkbox->setLabel("meow", font, {255, 255, 255, SDL_ALPHA_OPAQUE}, espeon::Checkbox::TEXT_ALIGN_LEFT);

        this->addElement(checkbox);

        auto primitive = new espeon::Primitive(
            {900, 100}, {500, 50}, {0, 0, 255, SDL_ALPHA_OPAQUE}
        );

        this->addElement(primitive);

        auto textInput = new espeon::TextInput(
            {900, 100}, {500, 50}, font, SDL_Color{255, 0, 0, SDL_ALPHA_OPAQUE}, "Placeholder"
        );

        textInput->onHover([]() {
            std::cout << "hello world!" << std::endl;
        });

        textInput->setLabel("World Seed", font, {255, 255, 255, SDL_ALPHA_OPAQUE});
        textInput->setCharacterLimit(8);

        this->addElement(textInput);

        this->addElement(new espeon::TextInput(
            {900, 300}, {500, 50}, font, SDL_Color{255, 0, 0, SDL_ALPHA_OPAQUE}, "Placeholder 2"
        ));

        auto progressBar = new espeon::ProgressBar(
            {300, 500}, {500, 50},
            {
                {500, 50}, SDL_Color{127, 127, 127, SDL_ALPHA_OPAQUE}
            },
            {
                {480, 30}, SDL_Color{0, 255, 0, SDL_ALPHA_OPAQUE}
            },
            0, 80
        );

        progressBar->onClick([=]() {
            progressBar->setValue(progressBar->getValue() + 10);
        });

        progressBar->onValueChanged([](float value) {
            std::cout << "value: " << value << std::endl;
        });

        this->addElement(progressBar);

        return true;
    }

public:
    static CustomScene* create(SDL_Renderer* renderer) {
        auto* ret = new CustomScene();
        if (!ret->setup(window, renderer)) {
            return nullptr;
        }
        return ret;
    }
};

espeon::SceneManager* sceneManager = espeon::SceneManager::get();

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_SetAppMetadata("espeon_lib_test", "1.0", "dev.limegradient.espeon_lib_test");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!TTF_Init()) {
        SDL_Log("Couldn't initialize TTF: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("espeon_test", 1280, 720, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_SetRenderLogicalPresentation(renderer, 1280, 720, SDL_LOGICAL_PRESENTATION_INTEGER_SCALE);

    SDL_SetRenderDrawColorFloat(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE_FLOAT);

    SDL_RenderClear(renderer);

    sceneManager->loadSceneWithWindow<LCETitleScreen>(window, renderer);

    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

bool dragging = false;
auto em = espeon::EventManager::get();
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }

    if (event->type == SDL_EVENT_WINDOW_SHOWN) {
        em->setEvent(event);
    }

    sceneManager->updateSceneEvents(event);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    sceneManager->updateScene();
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{

}