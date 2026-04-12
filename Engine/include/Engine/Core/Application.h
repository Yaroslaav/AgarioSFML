#pragma once

#include <string>

#include "Engine/Input/InputManager.h"
#include "Engine/View/Window.h"

namespace Engine
{
    class IGame;

    class Application
    {
    public:
        Application(unsigned int width, unsigned int height, const std::string& title);

        void Run(IGame& game);
        void Close();

        [[nodiscard]] Window& GetWindow()
        {
            return m_window;
        }
        [[nodiscard]] const Window& GetWindow() const
        {
            return m_window;
        }
        [[nodiscard]] InputManager& GetInput()
        {
            return m_input;
        }

    private:
        Window m_window;
        InputManager m_input;
    };
}
