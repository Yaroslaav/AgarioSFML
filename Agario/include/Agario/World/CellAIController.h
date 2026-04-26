#pragma once
#include "Engine/GameplayTags/GameplayTag.h"
#include "Engine/World/Controller/AIController.h"

namespace Agario
{
    class Cell;

    class CellAIController : public Engine::AIController
    {
    public:
        CellAIController() = default;

        explicit CellAIController(const BotSettings &settings);
        CellAIController(const BotSettings &settings, Actor* pawn);
        void BeginPlay(Engine::Application &app) override;

        void Tick(Engine::Application &app, float deltaTime) override;

    private:
        sf::Vector2f m_targetPosition;
        Engine::GameplayTag m_currentState;
    };
}
