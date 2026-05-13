#pragma once
#include "Agario/World/AgarioController.h"
#include "Engine/GameplayTags/GameplayTag.h"
#include "Engine/Helpers/Event.h"

#include <SFML/System/Vector2.hpp>

namespace Agario
{
    class Cell;

    class CellAIController : public AgarioController
    {
    public:
        CellAIController() = default;

        explicit CellAIController(const BotSettings &settings);
        CellAIController(const BotSettings &settings, Actor* pawn);
        void BeginPlay(Engine::Application &app) override;

        void Tick(Engine::Application &app, float deltaTime) override;

    protected:
        void OnCellPossessed(Cell& cell) override;
        void OnCellUnPossessed(Cell& cell) override;

    private:
        [[nodiscard]] Cell* FindNearestThreat(const Cell& cell) const;
        [[nodiscard]] sf::Vector2f GetFleeTarget(const Cell& cell, const Cell& threat) const;

        BotAISettings m_settings;
        sf::Vector2f m_targetPosition;
        Engine::GameplayTag m_currentState;
        Engine::Event<Actor*>::EventHandle m_onPawnDeathEventHandle{};
        float m_retargetTimer = 0.f;
    };
}
