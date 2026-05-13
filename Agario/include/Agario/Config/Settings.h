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
        float radiusPerMass = 5.f;
        float minSplitCellMass = 20.f;
    };

    struct PlayerSettings
    {
        float startMass = 100.f;
        float maxSpeed = 250.f;
        sf::Color color = sf::Color::White;
        sf::Vector2f spawnPosition{640.f, 360.f};
    };

    struct BotAISettings
    {
        float acceptableRadius = 0.f;
        bool useCellRadiusForAcceptance = true;
        float roamingRadius = 500.f;
        float retargetInterval = 1.5f;
        float threatDetectionRadius = 450.f;
        float fleeDistance = 650.f;
        float safeThreatRadiusMultiplier = 1.25f;
    };

    struct BotSettings
    {
        int count = 1;
        float startMass = 10.f;
        float maxSpeed = 180.f;
        float spawnPadding = 32.f;
        sf::Color color{120, 220, 120};
        BotAISettings ai;
    };

    struct FoodSettings
    {
        int count = 10000;
        float mass = .5f;
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
        sf::FloatRect bounds{{0.f, 0.f}, {4000.f, 4000.f}};
    };

    struct ChunkSettings
    {
        int columns = 50;
        int rows = 50;
        sf::Color gridColor{80, 80, 80, 120};
    };

    struct GameSettings : Engine::AppSettings
    {
        WorldSettings world;
        ChunkSettings chunks;
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
