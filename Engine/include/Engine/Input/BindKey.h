#pragma once

#include <functional>
#include <vector>

#include "Engine/GameplayTags/GameplayTag.h"
#include "Engine/Helpers/Event.h"
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

        [[nodiscard]] sf::Keyboard::Key GetKey() const
        {
            return m_key;
        }
        Event<> OnPressedOnce;
        Event<> OnHeld;
        Event<> OnReleased;

    private:
        GameplayTag m_actionTag;
        sf::Keyboard::Key m_key;

        bool m_wasPressed = false;
        bool m_isPressed = false;
    };
}
