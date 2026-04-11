#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

#include "Engine/Input/InputManager.h"

namespace Engine
{
    class IGame;

    class Application
    {
    public:
        Application(unsigned int width, unsigned int height, const std::string& title);

        void Run(IGame& game);
        void Close();

        [[nodiscard]] sf::RenderWindow& GetWindow()
        {
            return m_window;
        }
        [[nodiscard]] InputManager& GetInput()
        {
            return m_input;
        }

    private:
        sf::RenderWindow m_window;
        InputManager m_input;
    };
}
