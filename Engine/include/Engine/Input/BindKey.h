#pragma once

#include <functional>
#include <string>
#include <vector>

#include "SFML/Window/Keyboard.hpp"

namespace Engine
{
    class BindKey
    {
    public:
        BindKey(std::string actionName, sf::Keyboard::Key key);

        void CheckInput();
        void CheckKeyboardInput();

        void AssignOnKeyPress(std::function<void()> callback);
        void AssignOnKeyDown(std::function<void()> callback);
        void AssignOnKeyUp(std::function<void()> callback);

        [[nodiscard]] sf::Keyboard::Key GetKey() const
        {
            return m_key;
        }
    private:
        std::string m_actionName;
        sf::Keyboard::Key m_key = sf::Keyboard::Key::Unknown;

        bool m_wasPressed = false;
        bool m_isPressed = false;

        std::vector<std::function<void()>> m_OnPressed;
        std::vector<std::function<void()>> m_OnDown;
        std::vector<std::function<void()>> m_OnUp;
    };
}
