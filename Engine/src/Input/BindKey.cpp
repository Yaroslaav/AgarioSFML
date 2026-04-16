#include "Engine/Input/BindKey.h"

#include <utility>

namespace Engine
{
    BindKey::BindKey(GameplayTag actionTag, const sf::Keyboard::Key key) :
        m_actionTag(std::move(actionTag)), m_key(key)
    {
    }

    void BindKey::CheckInput()
    {
        CheckKeyboardInput();
    }

    void BindKey::CheckKeyboardInput()
    {
        m_isPressed = sf::Keyboard::isKeyPressed(m_key);

        if (!m_wasPressed && m_isPressed)
        {
            OnPressedOnce.Broadcast();
        }

        if (m_isPressed)
        {
            OnHeld.Broadcast();
        }

        if (m_wasPressed && !m_isPressed)
        {
            OnReleased.Broadcast();
        }

        m_wasPressed = m_isPressed;
    }
}
