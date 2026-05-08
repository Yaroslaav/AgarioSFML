#include "Agario/Config/Settings.h"
#include "Agario/World/CellAIController.h"

#include "Agario/GameplayTags/GameTags.h"
#include "Agario/World/AgarioWorld.h"
#include "Agario/World/Cell.h"
#include "Engine/Core/DebugSystem.h"
#include "Engine/GameplayTags/GameTags.h"
#include "Engine/Math/MathUtils.h"

namespace Agario
{
    CellAIController::CellAIController(const BotSettings &settings)
        : m_settings(settings.ai)
    {
        SetAcceptableRadius(settings.ai.acceptableRadius);
    }

    CellAIController::CellAIController(const BotSettings &settings, Engine::Actor *pawn)
        : AgarioController(pawn), m_settings(settings.ai)
    {
        SetAcceptableRadius(settings.ai.acceptableRadius);
    }

    void CellAIController::BeginPlay(Engine::Application &app)
    {
        AgarioController::BeginPlay(app);

        m_currentState = Tags::Agario::AI_State_Deciding;
    }

    void CellAIController::Tick(Engine::Application &app, const float deltaTime)
    {
        AgarioController::Tick(app, deltaTime);

        Cell* cell = GetPrimaryCell();
        if (cell == nullptr || !cell->IsActive())
        {
            return;
        }

        if (m_currentState == Tags::Agario::AI_State_Deciding)
        {
            auto* world = GetWorld<AgarioWorld>();
            if (!world)
            {
                return;
            }
            const auto& chunkGrid = world->GetChunkGrid();

            m_targetPosition = chunkGrid.GetBestFoodChunkPositionInRadius(cell->GetActorPosition(), m_settings.roamingRadius);

            if (Engine::Math::Distance(m_targetPosition, cell->GetActorPosition()) < GetAcceptableRadius())
            {
                m_targetPosition = chunkGrid.GetRandomChunkPositionInRadius(cell->GetActorPosition(), m_settings.roamingRadius);
            }

            m_currentState = Tags::Agario::AI_State_Roaming;
            m_retargetTimer = m_settings.retargetInterval;
        }
        if (m_currentState == Tags::Agario::AI_State_Roaming)
        {
            Engine::DebugSystem::DrawLine(cell->GetActorPosition(), m_targetPosition, sf::Color::Cyan);
            Engine::DebugSystem::DrawCircle(m_targetPosition, 10.f, sf::Color::Green);

            m_retargetTimer -= deltaTime;

            if (ReachedPosition(m_targetPosition) || Engine::Math::IsNearlyZero(m_targetPosition) || m_retargetTimer <= 0.f)
            {
                m_currentState = Tags::Agario::AI_State_Deciding;
                return;
            }

            MoveControlledCellsToward(m_targetPosition);
        }
    }

    void CellAIController::OnCellPossessed(Cell& cell)
    {
        m_onPawnDeathEventHandle = cell.OnDeath.AddListener([this](Actor* causer) mutable
        {
            m_currentState = Tags::Agario::AI_State_Deciding;
            m_targetPosition = {0.f, 0.f};
        });
    }

    void CellAIController::OnCellUnPossessed(Cell& cell)
    {
        cell.OnDeath.RemoveListener(m_onPawnDeathEventHandle);
    }
}
