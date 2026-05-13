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
        SetUseCellRadiusForAcceptance(settings.ai.useCellRadiusForAcceptance);
    }

    CellAIController::CellAIController(const BotSettings &settings, Engine::Actor *pawn)
        : AgarioController(pawn), m_settings(settings.ai)
    {
        SetAcceptableRadius(settings.ai.acceptableRadius);
        SetUseCellRadiusForAcceptance(settings.ai.useCellRadiusForAcceptance);
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

        if (Cell* threat = FindNearestThreat(*cell))
        {
            m_targetPosition = GetFleeTarget(*cell, *threat);
            m_currentState = Tags::Agario::AI_State_Fleeing;
        }
        else if (m_currentState == Tags::Agario::AI_State_Fleeing)
        {
            m_currentState = Tags::Agario::AI_State_Deciding;
        }

        if (m_currentState == Tags::Agario::AI_State_Fleeing)
        {
            Engine::DebugSystem::DrawLine(cell->GetActorPosition(), m_targetPosition, sf::Color::Red);
            Engine::DebugSystem::DrawCircle(m_targetPosition, 10.f, sf::Color::Red);

            MoveControlledCellsToward(m_targetPosition);
            return;
        }

        if (Cell* prey = FindNearestPrey(*cell))
        {
            m_targetPosition = prey->GetActorPosition();
            m_currentState = Tags::Agario::AI_State_Chasing;
        }
        else if (m_currentState == Tags::Agario::AI_State_Chasing)
        {
            m_currentState = Tags::Agario::AI_State_Deciding;
        }

        if (m_currentState == Tags::Agario::AI_State_Chasing)
        {
            Engine::DebugSystem::DrawLine(cell->GetActorPosition(), m_targetPosition, sf::Color(255, 160, 40));
            Engine::DebugSystem::DrawCircle(m_targetPosition, 10.f, sf::Color::Yellow);

            MoveControlledCellsToward(m_targetPosition);
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

    bool CellAIController::IsEnemyCellCandidate(const Cell& cell, const Cell* otherCell) const
    {
        if (otherCell == nullptr || otherCell == &cell || !otherCell->IsActive())
        {
            return false;
        }

        return cell.GetTeamId() == -1 || cell.GetTeamId() != otherCell->GetTeamId();
    }

    Cell* CellAIController::FindNearestThreat(const Cell& cell) const
    {
        const auto* world = GetWorld<AgarioWorld>();
        if (world == nullptr)
        {
            return nullptr;
        }

        Cell* nearestThreat = nullptr;
        float nearestThreatDistanceSquared = m_settings.threatDetectionRadius * m_settings.threatDetectionRadius;

        for (Cell* otherCell : world->GetAllActorsOfClass<Cell>())
        {
            if (!IsEnemyCellCandidate(cell, otherCell))
            {
                continue;
            }

            if (!otherCell->CanConsume(cell))
            {
                continue;
            }

            const float distanceSquared = Engine::Math::DistanceSquared(
                cell.GetActorPosition(),
                otherCell->GetActorPosition());
            if (distanceSquared < nearestThreatDistanceSquared)
            {
                nearestThreatDistanceSquared = distanceSquared;
                nearestThreat = otherCell;
            }
        }

        return nearestThreat;
    }

    Cell* CellAIController::FindNearestPrey(const Cell& cell) const
    {
        const auto* world = GetWorld<AgarioWorld>();
        if (world == nullptr)
        {
            return nullptr;
        }

        Cell* nearestPrey = nullptr;
        float nearestPreyDistanceSquared = m_settings.chaseDetectionRadius * m_settings.chaseDetectionRadius;

        for (Cell* otherCell : world->GetAllActorsOfClass<Cell>())
        {
            if (!IsEnemyCellCandidate(cell, otherCell))
            {
                continue;
            }

            if (!cell.CanConsume(*otherCell))
            {
                continue;
            }

            const float distanceSquared = Engine::Math::DistanceSquared(
                cell.GetActorPosition(),
                otherCell->GetActorPosition());
            if (distanceSquared < nearestPreyDistanceSquared)
            {
                nearestPreyDistanceSquared = distanceSquared;
                nearestPrey = otherCell;
            }
        }

        return nearestPrey;
    }

    sf::Vector2f CellAIController::GetFleeTarget(const Cell& cell, const Cell& threat) const
    {
        const sf::Vector2f cellPosition = cell.GetActorPosition();
        const sf::Vector2f threatPosition = threat.GetActorPosition();
        sf::Vector2f fleeDirection = Engine::Math::NormalizeOrZero(cellPosition - threatPosition);

        if (Engine::Math::IsNearlyZero(fleeDirection))
        {
            const auto* world = GetWorld<AgarioWorld>();
            if (world != nullptr && world->HasBounds())
            {
                const sf::FloatRect& bounds = world->GetBounds();
                const sf::Vector2f worldCenter = bounds.position + bounds.size * .5f;
                fleeDirection = Engine::Math::NormalizeOrZero(cellPosition - worldCenter);
            }
        }

        if (Engine::Math::IsNearlyZero(fleeDirection))
        {
            fleeDirection = {1.f, 0.f};
        }

        const float threatClearance = threat.GetRadius() * m_settings.safeThreatRadiusMultiplier;
        const sf::Vector2f fleeTarget = cellPosition + fleeDirection * (m_settings.fleeDistance + threatClearance);
        const auto* world = GetWorld<AgarioWorld>();
        if (world == nullptr || !world->HasBounds())
        {
            return fleeTarget;
        }

        return Engine::Math::ClampToRect(fleeTarget, world->GetBounds(), cell.GetRadius());
    }
}
