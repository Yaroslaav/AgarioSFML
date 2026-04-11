#include "Agario/Game.h"

#include <iostream>

#include "../../Engine/include/Engine/core/Application.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <optional>

namespace Agario
{
    void Game::OnInit(Engine::Application& app)
    {
        m_player.setRadius(30.f);
        m_player.setOrigin({30.f, 30.f});
        m_player.setPosition({640.f, 360.f});
    }

    void Game::OnEvent(Engine::Application& app)
    {
        auto& window = app.GetWindow();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                app.Close();
            }
        }
    }

    void Game::OnUpdate(Engine::Application& app, const float deltaTime)
    {
        sf::Vector2f movement = {0.f, 0.f};

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            movement.y -= m_speed * deltaTime;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            movement.y += m_speed * deltaTime;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            movement.x -= m_speed * deltaTime;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            movement.x += m_speed * deltaTime;
        }

        m_player.move(movement);
    }

    void Game::OnRender(Engine::Application& app)
    {
        app.GetWindow().draw(m_player);
    }

    void Game::OnShutdown(Engine::Application& app)
    {
    }
}