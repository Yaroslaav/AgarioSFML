#include "Engine/Input/InputManager.h"

#include <utility>

namespace Engine
{
    void InputManager::Update(const sf::RenderWindow& window)
    {
        CheckKeys();
        CheckMouseInput(window);
    }

    void InputManager::CheckMouseInput(const sf::RenderWindow& window)
    {
        m_lastMousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
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
