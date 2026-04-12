#pragma once

#include <deque>

#include "BindKey.h"
#include "Engine/View/Window.h"
#include "SFML/System/Vector2.hpp"

namespace Engine
{
    class InputManager
    {
    public:

        void Update(const Window& window);

        void CheckMouseInput(const Window& window);
        void CheckKeys();

        BindKey& AddNewBind(sf::Keyboard::Key key, GameplayTag actionTag);

        [[nodiscard]] sf::Vector2f GetLastMousePosition() const
        {
            return m_lastMousePosition;
        }
    private:
        std::deque<BindKey> m_keys;
        sf::Vector2f m_lastMousePosition = {0,0};
    };
}
