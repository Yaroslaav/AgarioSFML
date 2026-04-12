#include "Agario/Game.h"

#include "Engine/Core/Application.h"

#include <SFML/System/Vector2.hpp>
#include <optional>

namespace Agario
{
    void Game::OnInit(Engine::Application& app)
    {
        m_player.setRadius(30.f);
        m_player.setOrigin({30.f, 30.f});
        m_player.setPosition({640.f, 360.f});

        m_center.setRadius(10.f);
        m_center.setOrigin({10.f, 10.f});
        m_center.setPosition({640.f, 360.f});
    }

    void Game::OnEvent(Engine::Application& app)
    {
        auto& window = app.GetWindow();

        while (const std::optional event = window.PollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                app.Close();
            }
        }
    }

    void Game::OnUpdate(Engine::Application& app, const float deltaTime)
    {
        if (const sf::Vector2f dir = app.GetInput().GetLastMousePosition() - m_player.getPosition();
            dir.x != 0.f || dir.y != 0.f)
        {
            m_player.move(dir.normalized() * m_speed * deltaTime);
        }

    }

    void Game::OnRender(Engine::Application& app)
    {
        app.GetWindow().Draw(m_player);
        app.GetWindow().Draw(m_center);
    }

    void Game::OnShutdown(Engine::Application& app)
    {
    }
}
