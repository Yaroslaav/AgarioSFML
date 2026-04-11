#pragma once

#include <functional>
#include <vector>

#include "Engine/GameplayTags/GameplayTag.h"
#include "SFML/Window/Keyboard.hpp"

namespace Engine
{
    class BindKey
    {
    public:
        BindKey(GameplayTag actionTag, sf::Keyboard::Key key);
        BindKey(const BindKey&) = delete;
        BindKey& operator=(const BindKey&) = delete;
        BindKey(BindKey&&) = default;
        BindKey& operator=(BindKey&&) = default;

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
        GameplayTag m_actionTag;
        sf::Keyboard::Key m_key;

        bool m_wasPressed = false;
        bool m_isPressed = false;

        std::vector<std::function<void()>> m_OnPressed;
        std::vector<std::function<void()>> m_OnDown;
        std::vector<std::function<void()>> m_OnUp;
    };
}
