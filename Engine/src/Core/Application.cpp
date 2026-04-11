#include "../../include/Engine/Core/Application.h"
#include "../../include/Engine/Core/IGame.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

namespace Engine
{
    Application::Application(const unsigned int width, const unsigned int height, const std::string& title)
        : m_window(sf::VideoMode({width, height}), title)
    {
        m_window.setFramerateLimit(144);
    }

    void Application::Run(IGame& game)
    {
        game.OnInit(*this);

        sf::Clock clock;

        while (m_window.isOpen())
        {
            const float deltaTime = clock.restart().asSeconds();

            m_input.Update(m_window);

            game.OnEvent(*this);
            game.OnUpdate(*this, deltaTime);

            m_window.clear(sf::Color::Black);
            game.OnRender(*this);
            m_window.display();
        }

        game.OnShutdown(*this);
    }

    void Application::Close()
    {
        m_window.close();
    }
}