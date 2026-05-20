#pragma once

#include "Engine/View/Window.h"

#include <SFML/Graphics/Font.hpp>

namespace Agario
{
    class AgarioWorld;

    class GameUI
    {
    public:
        bool Initialize();
        void ToggleHelp();
        void Render(Engine::Window& window, const AgarioWorld& world) const;

    private:
        void RenderHelp(Engine::Window& window) const;
        void RenderLeaderboard(Engine::Window& window, const AgarioWorld& world) const;

        sf::Font m_font;
        bool m_isHelpOpen = false;
        bool m_hasFont = false;
    };
}
