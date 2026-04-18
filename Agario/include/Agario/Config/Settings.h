#pragma once

#include "Engine/Config/Settings.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace Agario
{
    struct ConsumeSettings
    {
        float thresholdRatio = 0.8f;
        float massGainFactor = 0.4f;
    };

    struct PlayerSettings
    {
        float radius = 30.f;
        float startMass = 5.f;
        float maxSpeed = 250.f;
        sf::Color color = sf::Color::White;
        sf::Vector2f spawnPosition{640.f, 360.f};
    };

    struct BotAISettings
    {
        float roamingRadius = 220.f;
        float retargetInterval = 1.5f;
        float acceptableRadius = 4.f;
    };

    struct BotSettings
    {
        int count = 1;
        float radius = 30.f;
        float startMass = 5.f;
        float maxSpeed = 180.f;
        float spawnPadding = 32.f;
        sf::Color color{120, 220, 120};
        BotAISettings ai;
    };

    struct FoodSettings
    {
        int count = 2000;
        float mass = .1f;
        float spawnPadding = 12.f;
        float radius = 2.f;
        sf::Color color{255, 210, 70};
    };

    struct GameplaySettings
    {
        ConsumeSettings consume;
    };

    struct WorldSettings
    {
        sf::FloatRect bounds{{0.f, 0.f}, {2000.f, 2000.f}};
    };

    struct GameSettings : Engine::AppSettings
    {
        WorldSettings world;
        PlayerSettings player;
        BotSettings bots;
        FoodSettings food;
        GameplaySettings gameplay;

        GameSettings()
        {
            window.title = "Agario";
            render.clearColor = sf::Color(18, 18, 18);
        }
    };

    inline const GameSettings Settings{};
}
