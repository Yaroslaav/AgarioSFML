#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

namespace Engine
{
    class IGame;

    class Application
    {
    public:
        Application(unsigned int width, unsigned int height, const std::string& title);

        void Run(IGame& game);
        void Close();

        sf::RenderWindow& GetWindow();

    private:
        sf::RenderWindow m_window;
    };
}