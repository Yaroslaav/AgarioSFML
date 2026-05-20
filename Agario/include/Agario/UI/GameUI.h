#pragma once

#include "Engine/View/Window.h"

#include <SFML/Graphics/Font.hpp>

namespace Agario
{
    class GameUI
    {
    public:
        bool Initialize();
        void ToggleHelp();
        void Render(Engine::Window& window) const;

    private:
        sf::Font m_font;
        bool m_isHelpOpen = false;
        bool m_hasFont = false;
    };
}
