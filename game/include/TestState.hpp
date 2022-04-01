#pragma once

#include <SFML/Graphics.hpp>
#include <cstdio>

#include <imgui.h>

#include "Animation.hpp"
#include "AudioManager.hpp"
#include "ContentManager.hpp"
#include "CustomMath.hpp"
#include "GameState.hpp"
#include "Animation.hpp"
#include "Tileset.hpp"
#include "AnimatedSprite.hpp"

enum class AnimationType
{
    Attack1,
    Attack2,
    Death,
    Fall,
    Idle,
    Jump,
    Run,
    TakeHit,
    Count
};

#define STRINGIFY(x) (#x)

const const char *animationTypes[] = {
    STRINGIFY(AnimationType::Attack1), STRINGIFY(AnimationType::Attack2),
    STRINGIFY(AnimationType::Death),   STRINGIFY(AnimationType::Fall),
    STRINGIFY(AnimationType::Idle),    STRINGIFY(AnimationType::Jump),
    STRINGIFY(AnimationType::Run),     STRINGIFY(AnimationType::TakeHit)};

int animationTypeIndex;

class TestState : public gjt::GameState
{
  private:
    std::shared_ptr<sf::Font> font;
    sf::Text fpsText;
    char fpsBuffer[32];
    

    gjt::AnimatedSprite<AnimationType> animatedSprite;

  public:
    TestState(gjt::Game *const game, gjt::ServiceLocator *const services) : gjt::GameState(game, services)
    {
    }

    virtual void load() override
    {
        auto content = services->resolve<gjt::ContentManager>();
        font =
            content->loadFromFile<sf::Font>("content/monogram-extended.ttf");
        
        animatedSprite.addAnimation(
            AnimationType::Attack1,
            std::make_shared<gjt::Animation>(
                std::make_shared<gjt::Tileset>(
                    content->loadFromFile<sf::Texture>("content/Attack1.png"),
                    250, 250),
                7, 0.7f, true));

        animatedSprite.addAnimation(
            AnimationType::Attack2,
            std::make_shared<gjt::Animation>(
                std::make_shared<gjt::Tileset>(
                    content->loadFromFile<sf::Texture>("content/Attack2.png"),
                    250, 250),
                8, 0.8f, true));

        animatedSprite.addAnimation(
            AnimationType::Death,
            std::make_shared<gjt::Animation>(
                std::make_shared<gjt::Tileset>(
                    content->loadFromFile<sf::Texture>("content/Death.png"),
                    250, 250),
                7, 0.7f, true));

        animatedSprite.addAnimation(
            AnimationType::Fall,
            std::make_shared<gjt::Animation>(
                std::make_shared<gjt::Tileset>(
                    content->loadFromFile<sf::Texture>("content/Fall.png"),
                    250, 250),
                2, 0.2f, true));

        animatedSprite.addAnimation(
            AnimationType::Idle,
            std::make_shared<gjt::Animation>(
                std::make_shared<gjt::Tileset>(
                    content->loadFromFile<sf::Texture>("content/Idle.png"),
                    250, 250),
                8, 0.8f, true));

        animatedSprite.addAnimation(
            AnimationType::Jump,
            std::make_shared<gjt::Animation>(
                std::make_shared<gjt::Tileset>(
                    content->loadFromFile<sf::Texture>("content/Jump.png"),
                    250, 250),
                2, 0.2f, true));

        animatedSprite.addAnimation(
            AnimationType::Run,
            std::make_shared<gjt::Animation>(
                std::make_shared<gjt::Tileset>(
                    content->loadFromFile<sf::Texture>("content/Run.png"),
                    250, 250),
                8, 0.8f, true));

        animatedSprite.addAnimation(
            AnimationType::TakeHit,
            std::make_shared<gjt::Animation>(
                std::make_shared<gjt::Tileset>(
                    content->loadFromFile<sf::Texture>("content/Take hit.png"), 250,
                    250),
                3, 0.3f, true));

        animatedSprite.setAnimationKey(AnimationType::Attack1);
        animatedSprite.setPosition(300, 250);
        animatedSprite.setScale(3, 3);
        animatedSprite.setOrigin(125, 125);

        fpsText.setFont(*font);
        fpsText.setCharacterSize(64);
        fpsText.setFillColor(sf::Color::Black);
        fpsText.setPosition(
            {game->getWindowWidth() / 2.0f, game->getWindowHeight() / 2.0f});
        game->setClearColor(sf::Color(0xffb200ff));

        animationTypeIndex = 0;
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

        animatedSprite.update(dt);
    }

    virtual void ui(float dt) override
    {
        if (ImGui::Begin("debug animation"))
        {
            if (ImGui::Button("start"))
            {
                animatedSprite.getCurrentAnimation()->start();
            }
            ImGui::SameLine();
            if (ImGui::Button("stop"))
            {
                animatedSprite.getCurrentAnimation()->stop();
            }
            ImGui::SameLine();
            if (ImGui::Button("reset"))
            {
                animatedSprite.getCurrentAnimation()->reset();
            }
            
            if (ImGui::Checkbox(
                    "reverse",
                    &animatedSprite.getCurrentAnimation()->getReverse()))
            {
            
            }

            if (ImGui::SliderFloat(
                    "time scale",
                    &animatedSprite.getCurrentAnimation()->getScale(), 0.1f,
                    1.0f))
            {
            }

            if (ImGui::BeginCombo("animations", animationTypes[animationTypeIndex]))
            {
                for (uint32_t i = 0; i < (uint32_t)AnimationType::Count; ++i)
                {
                    if (ImGui::Selectable(
                            animationTypes[i], animationTypeIndex == i))
                    {
                        animationTypeIndex = i;
                        animatedSprite.setAnimationKey((AnimationType)i);
                        animatedSprite.getCurrentAnimation()->start();
                    }
                }

                ImGui::EndCombo();
            }

            ImGui::End();
        }
    }

    virtual void draw(
        float dt, sf::RenderTarget &target,
        sf::RenderStates states = sf::RenderStates()) override
    {
        /*target.draw(fpsText, states);

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

        target.draw(lines, 4, sf::PrimitiveType::Lines);*/

        target.draw(animatedSprite, states);
    }
};
