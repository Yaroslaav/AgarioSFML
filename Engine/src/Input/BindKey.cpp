#include "Engine/Input/BindKey.h"

namespace Engine
{
    BindKey::BindKey(std::string actionName, sf::Keyboard::Key key) :
        m_actionName(std::move(actionName)), m_key(key)
    {
    }

    void BindKey::CheckInput()
    {
        CheckKeyboardInput();
    }

    void BindKey::CheckKeyboardInput()
    {
        m_isPressed = sf::Keyboard::isKeyPressed(m_key);

        if (m_wasPressed && !m_isPressed)
        {
            for (auto& cb : m_OnUp)
                cb();
        }
        else if (m_wasPressed)
        {
            for (auto& cb : m_OnPressed)
                cb();
        }
        else if (m_isPressed)
        {
            for (auto& cb : m_OnDown)
                cb();
        }
        m_wasPressed = m_isPressed;
    }

    void BindKey::AssignOnKeyPress(std::function<void()> callback)
    {
        m_OnPressed.push_back(std::move(callback));
    }

    void BindKey::AssignOnKeyDown(std::function<void()> callback)
    {
        m_OnDown.push_back(std::move(callback));
    }

    void BindKey::AssignOnKeyUp(std::function<void()> callback)
    {
        m_OnUp.push_back(std::move(callback));
    }
}
