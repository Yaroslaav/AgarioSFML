#include "Engine/Core/Application.h"
#include "Engine/Core/IGame.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Clock.hpp>

namespace Engine
{
    Application::Application(const unsigned int width, const unsigned int height, const std::string& title)
        : m_window(width, height, title, 144)
    {
        m_window.Init(*this);
    }

    void Application::Run(IGame& game)
    {
        game.OnInit(*this);

        sf::Clock clock;

        while (m_window.IsOpen())
        {
            const float deltaTime = clock.restart().asSeconds();

            m_input.Update(m_window);

            game.OnEvent(*this);
            game.OnUpdate(*this, deltaTime);

            m_window.Clear(sf::Color::Black);
            m_renderSystem.DrawAll(m_window);
            game.OnRender(*this);
            m_window.Display();
        }

        game.OnShutdown(*this);
    }

    void Application::Close()
    {
        m_window.Close();
    }
}
