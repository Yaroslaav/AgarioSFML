#include "Engine/Input/InputManager.h"

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

    BindKey& InputManager::AddNewBind(sf::Keyboard::Key key, std::string &name)
    {
        m_keys.emplace_back(name, key);
        return m_keys.back();
    }
}
