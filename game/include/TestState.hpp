#pragma once

#include <SFML/Graphics.hpp>
#include <cstdio>

#include <imgui.h>

#include "AudioManager.hpp"
#include "ContentManager.hpp"
#include "CustomMath.hpp"
#include "GameState.hpp"

class TestState : public gjt::GameState
{
  private:
    std::shared_ptr<sf::Font> font;
    sf::Text fpsText;
    char fpsBuffer[32];

    std::shared_ptr<sf::SoundBuffer> sound;

  public:
    TestState(gjt::Game *const game, gjt::ServiceLocator *const services) : gjt::GameState(game, services)
    {
    }

    virtual void load() override
    {
        auto content = services->resolve<gjt::ContentManager>();
        font =
            content->loadFromFile<sf::Font>("content/monogram-extended.ttf");
        
        fpsText.setFont(*font);
        fpsText.setCharacterSize(64);
        fpsText.setFillColor(sf::Color::Black);
        fpsText.setPosition(
            {game->getWindowWidth() / 2.0f, game->getWindowHeight() / 2.0f});
        game->setClearColor(sf::Color(0xffb200ff));

        auto audio = services->resolve<gjt::AudioManager<std::string>>();
        if (audio == nullptr)
        {
            services->registerInstance<gjt::AudioManager<std::string>>();
            audio = services->resolve<gjt::AudioManager<std::string>>();
        }

        sound = content->loadFromFile<sf::SoundBuffer>("content/lost_old.ogg");
        audio->createSound("test", sound);
        audio->queue("test", true);
        audio->setGeneralVolume(0.5f);
    }

    virtual void update(float dt) override
    {
        const float fps = 1 / dt;
        sprintf_s(fpsBuffer, "FPS: %7.2f", fps);
        fpsText.setString(fpsBuffer);

        const sf::FloatRect bounds = fpsText.getLocalBounds();
        fpsText.setPosition(
            {game->getWindowWidth() / 2.0f - bounds.left,
             game->getWindowHeight() / 2.0f - bounds.top});
        fpsText.setOrigin({bounds.width / 2.0f, bounds.height / 2.0f});
    }

    virtual void ui(float dt) override
    {
       if (ImGui::Begin("test"))
        {
            if (ImGui::Button("click me"))
            {
                printf("clicked!\n");
            }

            ImGui::End();
        }
    }

    virtual void draw(
        float dt, sf::RenderTarget &target,
        sf::RenderStates states = sf::RenderStates()) override
    {
        target.draw(fpsText, states);

        sf::Vertex lines[4] = {
            sf::Vertex(
                sf::Vector2f(0, game->getWindowHeight() / 2.0f),
                sf::Color(0x000000aa)),
            sf::Vertex(
                sf::Vector2f(
                    game->getWindowWidth(), game->getWindowHeight() / 2.0f),
                sf::Color(0x000000aa)),
            sf::Vertex(
                sf::Vector2f(game->getWindowWidth() / 2.0f, 0),
                sf::Color(0x000000aa)),
            sf::Vertex(
                sf::Vector2f(
                    game->getWindowWidth() / 2.0f, game->getWindowHeight()),
                sf::Color(0x000000aa))};

        target.draw(lines, 4, sf::PrimitiveType::Lines);
    }
};
