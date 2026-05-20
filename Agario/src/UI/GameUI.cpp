#include "Agario/UI/GameUI.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include <iostream>

namespace Agario
{
    bool GameUI::Initialize()
    {
        m_hasFont = m_font.openFromFile("assets/Fonts/Tuffy/Tuffy-Regular.ttf");

        if (!m_hasFont)
        {
            std::cout << "Failed to load UI font\n";
        }

        return m_hasFont;
    }

    void GameUI::ToggleHelp()
    {
        m_isHelpOpen = !m_isHelpOpen;
    }

    void GameUI::Render(Engine::Window& window) const
    {
        if (!m_hasFont)
        {
            return;
        }

        sf::RectangleShape helpButton({92.f, 34.f});
        helpButton.setPosition({12.f, 12.f});
        helpButton.setFillColor(sf::Color(28, 34, 40, 220));
        helpButton.setOutlineColor(sf::Color(230, 235, 240, 180));
        helpButton.setOutlineThickness(1.f);
        window.DrawScreen(helpButton);

        sf::Text helpText(m_font, "Help (H)", 18);
        helpText.setPosition({24.f, 18.f});
        helpText.setFillColor(sf::Color::White);
        window.DrawScreen(helpText);

        if (!m_isHelpOpen)
        {
            return;
        }

        sf::RectangleShape panel({310.f, 300.f});
        panel.setPosition({12.f, 56.f});
        panel.setFillColor(sf::Color(16, 20, 24, 235));
        panel.setOutlineColor(sf::Color(230, 235, 240, 160));
        panel.setOutlineThickness(1.f);
        window.DrawScreen(panel);

        sf::Text title(m_font, "Keybinds", 22);
        title.setPosition({28.f, 72.f});
        title.setFillColor(sf::Color::White);
        window.DrawScreen(title);

        sf::Text instructions(
            m_font,
            "Move: mouse cursor\n"
            "Split: Space\n"
            "Toggle fullscreen: F11\n"
            "Zoom: = / -\n"
            "Toggle debug: F1\n"
            "Toggle chunk debug: Numpad1\n"
            "Toggle debug traces: Numpad2\n"
            "Close help: H\n"
            "Quit: Escape",
            16);
        instructions.setPosition({28.f, 112.f});
        instructions.setFillColor(sf::Color(225, 230, 235));
        instructions.setLineSpacing(1.15f);
        window.DrawScreen(instructions);
    }
}
