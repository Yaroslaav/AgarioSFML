#include "Agario/Config/Settings.h"
#include "Agario/World/CellAIController.h"

#include "Agario/GameplayTags/GameTags.h"
#include "Agario/World/AgarioWorld.h"
#include "Agario/World/Cell.h"
#include "Engine/Components/MovementComponent.h"
#include "Engine/Core/DebugSystem.h"
#include "Engine/GameplayTags/GameTags.h"
#include "Engine/Math/MathUtils.h"

namespace Agario
{
    CellAIController::CellAIController(const BotSettings &settings)
        : AIController(settings.ai), m_settings(settings.ai)
    {
    }

    CellAIController::CellAIController(const BotSettings &settings, Engine::Actor *pawn)
        : AIController(settings.ai, pawn), m_settings(settings.ai)
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

            movementComponent->AddInputVector(Engine::Math::NormalizeOrZero(m_targetPosition - cell->GetActorPosition()));
        }
    }

    void CellAIController::OnPossess(Actor &pawn)
    {
        m_onPawnDeathEventHandle = GetPawn<Cell>()->OnDeath.AddListener([this](Actor* causer) mutable
        {
            m_currentState = Tags::Agario::AI_State_Deciding;
            m_targetPosition = {0.f, 0.f};
        });
    }

    void CellAIController::OnUnPossess()
    {
        if (auto* cell = GetPawn<Cell>())
        {
            cell->OnDeath.RemoveListener(m_onPawnDeathEventHandle);
        }
    }
}
