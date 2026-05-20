#include "Agario/UI/GameUI.h"

#include "Agario/Actors/Cell.h"
#include "Agario/World/AgarioWorld.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include <algorithm>
#include <cmath>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>

namespace Agario
{
    namespace
    {
        struct LeaderboardEntry
        {
            std::string nickname;
            float mass = 0.f;
        };
    }

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

    void GameUI::Render(Engine::Window& window, const AgarioWorld& world) const
    {
        if (!m_hasFont)
        {
            return;
        }

        RenderHelp(window);
        RenderLeaderboard(window, world);
    }

    void GameUI::RenderHelp(Engine::Window& window) const
    {
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

    void GameUI::RenderLeaderboard(Engine::Window& window, const AgarioWorld& world) const
    {
        std::unordered_map<int, LeaderboardEntry> entriesByTeam;

        for (const Cell* cell : world.GetAllActorsOfClass<Cell>())
        {
            if (cell == nullptr || !cell->IsActive())
            {
                continue;
            }

            const int teamId = cell->GetTeamId();
            LeaderboardEntry& entry = entriesByTeam[teamId];
            if (entry.nickname.empty())
            {
                entry.nickname = cell->GetNickname().empty() ? "unknown" : cell->GetNickname();
            }

            entry.mass += cell->GetMass();
        }

        std::vector<LeaderboardEntry> entries;
        entries.reserve(entriesByTeam.size());
        for (const auto& pair : entriesByTeam)
        {
            entries.push_back(pair.second);
        }

        std::sort(
            entries.begin(),
            entries.end(),
            [](const LeaderboardEntry& left, const LeaderboardEntry& right)
            {
                return left.mass > right.mass;
            });

        constexpr std::size_t maxRows = 8;
        const std::size_t rowCount = std::min(maxRows, entries.size());

        const sf::Vector2f windowSize = static_cast<sf::Vector2f>(window.GetSize());
        const sf::Vector2f panelSize{230.f, 48.f + static_cast<float>(rowCount) * 24.f};
        const sf::Vector2f panelPosition{windowSize.x - panelSize.x - 12.f, 12.f};

        sf::RectangleShape panel(panelSize);
        panel.setPosition(panelPosition);
        panel.setFillColor(sf::Color(16, 20, 24, 220));
        panel.setOutlineColor(sf::Color(230, 235, 240, 150));
        panel.setOutlineThickness(1.f);
        window.DrawScreen(panel);

        sf::Text title(m_font, "Leaderboard", 20);
        title.setPosition(panelPosition + sf::Vector2f{14.f, 10.f});
        title.setFillColor(sf::Color::White);
        window.DrawScreen(title);

        for (std::size_t i = 0; i < rowCount; ++i)
        {
            const LeaderboardEntry& entry = entries[i];
            const std::string rankText = std::to_string(i + 1) + ". " + entry.nickname;
            const std::string massText = std::to_string(static_cast<int>(std::round(entry.mass)));
            const float rowY = panelPosition.y + 42.f + static_cast<float>(i) * 24.f;

            sf::Text name(m_font, rankText, 16);
            name.setPosition({panelPosition.x + 14.f, rowY});
            name.setFillColor(sf::Color(225, 230, 235));
            window.DrawScreen(name);

            sf::Text mass(m_font, massText, 16);
            const sf::FloatRect massBounds = mass.getLocalBounds();
            mass.setOrigin({massBounds.position.x + massBounds.size.x, massBounds.position.y});
            mass.setPosition({panelPosition.x + panelSize.x - 14.f, rowY});
            mass.setFillColor(sf::Color(225, 230, 235));
            window.DrawScreen(mass);
        }
    }
}
