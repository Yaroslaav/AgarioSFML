#pragma once

#include <string>

#include "Engine/Config/Settings.h"
#include "Engine/Input/InputManager.h"
#include "Engine/View/RenderSystem.h"
#include "Engine/View/Window.h"

namespace Engine
{
    class IGame;

    class Application
    {
    public:
        explicit Application(const AppSettings& settings);
        Application(
            unsigned int width,
            unsigned int height,
            const std::string& title,
            unsigned int frameRate = 144,
            sf::Color clearColor = sf::Color::Black,
            sf::Keyboard::Key fullscreenToggleKey = sf::Keyboard::Key::F11,
            bool startFullscreen = false);

        void Run(IGame& game);
        void Close();

        [[nodiscard]] Window& GetWindow()
        {
            return m_window;
        }
        [[nodiscard]] const Window& GetWindow() const
        {
            return m_window;
        }
        [[nodiscard]] InputManager& GetInput()
        {
            return m_input;
        }
        [[nodiscard]] RenderSystem& GetRenderSystem()
        {
            return m_renderSystem;
        }
        [[nodiscard]] const RenderSystem& GetRenderSystem() const
        {
            return m_renderSystem;
        }

    private:
        Window m_window;
        InputManager m_input;
        RenderSystem m_renderSystem;
        sf::Color m_clearColor = sf::Color::Black;
    };
}
