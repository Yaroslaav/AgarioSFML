#include "Engine/Core/Application.h"
#include "Engine/Core/IGame.h"
#include "Engine/Core/DebugDraw.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Clock.hpp>

namespace Engine
{
    Application::Application(const AppSettings& settings)
        : Application(
            settings.window.width,
            settings.window.height,
            settings.window.title,
            settings.render.frameRateLimit,
            settings.render.clearColor,
            settings.input.fullscreenToggleKey,
            settings.input.zoomInKey,
            settings.input.zoomOutKey,
            settings.input.zoomInFactor,
            settings.input.zoomOutFactor,
            settings.window.startFullscreen)
    {
        m_isDebugMode = settings.debug.startDebugMode;
    }

    Application::Application(
        const unsigned int width,
        const unsigned int height,
        const std::string& title,
        const unsigned int frameRate,
        const sf::Color clearColor,
        const sf::Keyboard::Key fullscreenToggleKey,
        const sf::Keyboard::Key zoomInKey,
        const sf::Keyboard::Key zoomOutKey,
        const float zoomInFactor,
        const float zoomOutFactor,
        const bool startFullscreen)
        : m_window(
            width,
            height,
            title,
            frameRate,
            fullscreenToggleKey,
            zoomInKey,
            zoomOutKey,
            zoomInFactor,
            zoomOutFactor,
            startFullscreen),
          m_clearColor(clearColor)
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

            m_window.Clear(m_clearColor);
            m_renderSystem.DrawAll(m_window);
            game.OnRender(*this);
            DebugDraw::Render(*this);
            m_window.Display();
        }

        game.OnShutdown(*this);
    }

    void Application::Close()
    {
        m_window.Close();
    }
}
