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
        : AIController(settings)
    {
    }

    CellAIController::CellAIController(const BotSettings &settings, Engine::Actor *pawn)
        : AIController(settings, pawn)
    {
    }

    void CellAIController::BeginPlay(Engine::Application &app)
    {
        AIController::BeginPlay(app);

        m_currentState = Tags::Agario::AI_State_Deciding;
    }

    void CellAIController::Tick(Engine::Application &app, const float deltaTime)
    {
        AIController::Tick(app, deltaTime);

        Cell* cell = GetPawn<Cell>();
        if (cell == nullptr || !cell->IsActive())
        {
            return;
        }

        auto* movementComponent = cell->GetComponent<Engine::MovementComponent>();
        if (movementComponent == nullptr)
        {
            return;
        }

        if (m_currentState == Tags::Agario::AI_State_Deciding)
        {
            if (auto* world = GetWorld<AgarioWorld>())
            {
                auto& chunkGrid = world->GetChunkGrid();
                m_targetPosition = chunkGrid.GetBestFoodChunkPosition(cell->GetActorPosition(), Settings.bots.ai.roamingRadius);
                
                if (Engine::Math::Distance(m_targetPosition, cell->GetActorPosition()) < GetAcceptableRadius())
                {
                    m_targetPosition = GetRandomLocationInRadius(cell->GetActorPosition(), Settings.bots.ai.roamingRadius);
                }
            }
            else
            {
                m_targetPosition = GetRandomLocationInRadius(cell->GetActorPosition(), Settings.bots.ai.roamingRadius);
            }
            
            m_currentState = Tags::Agario::AI_State_Roaming;
        }
        if (m_currentState == Tags::Agario::AI_State_Roaming)
        {
            Engine::DebugSystem::DrawLine(cell->GetActorPosition(), m_targetPosition, sf::Color::Cyan);
            Engine::DebugSystem::DrawCircle(m_targetPosition, 10.f, sf::Color::Green);

            if (ReachedPosition(m_targetPosition) || Engine::Math::IsNearlyZero(m_targetPosition))
            {
                m_currentState = Tags::Agario::AI_State_Deciding;
                return;
            }

            movementComponent->AddInputVector(Engine::Math::NormalizeOrZero(m_targetPosition - cell->GetActorPosition()));
        }
    }
}
