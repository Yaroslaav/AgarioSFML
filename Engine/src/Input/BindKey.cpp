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
            for (auto& cb : m_OnPressedOnce)
                cb();
        }

        if (m_isPressed)
        {
            for (auto& cb : m_OnHeld)
                cb();
        }

        if (m_wasPressed && !m_isPressed)
        {
            for (auto& cb : m_OnReleased)
                cb();
        }

        m_wasPressed = m_isPressed;
    }

    void BindKey::AssignOnKeyPressedOnce(std::function<void()> callback)
    {
        m_OnPressedOnce.push_back(std::move(callback));
    }

    void BindKey::AssignOnKeyHeld(std::function<void()> callback)
    {
        m_OnHeld.push_back(std::move(callback));
    }

    void BindKey::AssignOnKeyReleased(std::function<void()> callback)
    {
        m_OnReleased.push_back(std::move(callback));
    }
}
