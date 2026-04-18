#include "Agario/World/CellAIController.h"

#include "Agario/GameplayTags/GameTags.h"
#include "Engine/GameplayTags/GameTags.h"
#include "Engine/Math/MathUtils.h"

namespace Agario
{
    CellAIController::CellAIController(const BotSettings &settings)
        : AIController(settings)
    {
    }

    CellAIController::CellAIController(const BotSettings &settings, Actor *pawn)
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

        Actor* pawn = GetPawn();
        if (pawn == nullptr || !pawn->IsActive())
        {
            return;
        }

        auto* movementComponent = pawn->GetComponent<Engine::MovementComponent>();
        if (movementComponent == nullptr)
        {
            return;
        }

        if (m_currentState == Tags::Agario::AI_State_Deciding)
        {
            m_targetPosition = GetRandomLocationInRadius(GetPawn()->GetActorPosition(), 500);
            m_currentState = Tags::Agario::AI_State_Roaming;
        }
        else if (m_currentState == Tags::Agario::AI_State_Roaming)
        {
            if (ReachedPosition(m_targetPosition) || Engine::Math::IsNearlyZero(m_targetPosition))
            {
                m_currentState = Tags::Agario::AI_State_Deciding;
                return;
            }

            movementComponent->AddInputVector(Engine::Math::NormalizeOrZero(m_targetPosition - GetPawn()->GetActorPosition()));
        }
    }
}
