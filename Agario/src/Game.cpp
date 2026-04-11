#include "Agario/Game.h"

#include <iostream>

#include "../../Engine/include/Engine/Core/Application.h"

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

        sf::Vector2f dir = app.GetInput().GetLastMousePosition() - m_player.getPosition();
        if (dir.x != 0.f || dir.y != 0.f)
        {
            m_player.move(dir.normalized() * m_speed * deltaTime);
        }

    }

    void Game::OnRender(Engine::Application& app)
    {
        app.GetWindow().draw(m_player);
    }

    void Game::OnShutdown(Engine::Application& app)
    {
    }
}