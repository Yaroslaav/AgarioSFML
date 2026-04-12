#include "Engine/Input/InputManager.h"

#include <utility>

namespace Engine
{
    void InputManager::Update(const Window& window)
    {
        CheckKeys();
        CheckMouseInput(window);
    }

    void InputManager::CheckMouseInput(const Window& window)
    {
        m_lastMousePosition = window.MapPixelToCoords(window.GetMousePixelPosition());
    }

    void InputManager::CheckKeys()
    {
        for (auto& bind : m_keys)
        {
            bind.CheckInput();
        }
    }

    BindKey& InputManager::AddNewBind(sf::Keyboard::Key key, GameplayTag actionTag)
    {
        m_keys.emplace_back(std::move(actionTag), key);
        return m_keys.back();
    }
}
