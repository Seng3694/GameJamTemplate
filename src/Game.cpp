#include "Game.hpp"

#include <cassert>
#include "AudioManager.hpp"
#include "ContentManager.hpp"

namespace gjt
{
Game::Game(
    const std::string &title, const uint32_t width, const uint32_t height)
    : services(), windowWidth(width), windowHeight(height)
{
    window.create(
        sf::VideoMode(width, height), title,
        sf::Style::Close | sf::Style::Titlebar);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
}

void Game::switchScene(
    std::shared_ptr<GameScene> instance, bool unloadPrevious, bool loadNext)
{
    if (currentScene != nullptr && unloadPrevious)
    {
        currentScene->unload();
    }

    currentScene = instance;

    if (loadNext)
        currentScene->load();
}

void Game::run()
{
    load();
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        float dtf = dt.asSeconds();

        sf::Event e;

        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();
            else
            {
                handleEvent(e, dtf);
            }
        }

        window.clear(clearColor);

        ui(dtf);
        update(dtf);
        draw(dtf, window);

        window.display();
    }

    unload();
}

void Game::load()
{
}

void Game::update(float dt)
{
    assert(currentScene != nullptr);
    currentScene->update(dt);
}

void Game::ui(float dt)
{
    assert(currentScene != nullptr);
    currentScene->ui(dt);
}

void Game::draw(float dt, sf::RenderTarget &target, sf::RenderStates states)
{
    assert(currentScene != nullptr);
    currentScene->draw(dt, target, states);
}

void Game::handleEvent(const sf::Event &e, float dt)
{
    assert(currentScene != nullptr);
    currentScene->handleEvent(e, dt);
}

void Game::unload()
{
}
} // namespace gjt
