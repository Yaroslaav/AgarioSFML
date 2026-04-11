#pragma once

#include <string>
#include <vector>

#include "BindKey.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"

namespace Engine
{
    class InputManager
    {
    public:

        void Update(const sf::RenderWindow& window);

        void CheckMouseInput(const sf::RenderWindow& window);
        void CheckKeys();

        BindKey& AddNewBind(sf::Keyboard::Key key, std::string& name);

        [[nodiscard]] sf::Vector2f GetLastMousePosition() const
        {
            return m_lastMousePosition;
        }
    private:
        std::vector<BindKey> m_keys;
        sf::Vector2f m_lastMousePosition = {0,0};
    };
}
