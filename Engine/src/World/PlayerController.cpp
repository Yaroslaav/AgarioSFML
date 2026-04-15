#include "Engine/World/Controller/PlayerController.h"

#include <cmath>

#include "Engine/Core/Application.h"

namespace Engine
{
    namespace
    {
        sf::Vector2f NormalizeOrZero(const sf::Vector2f vector)
        {
            const float lengthSquared = vector.x * vector.x + vector.y * vector.y;
            if (lengthSquared <= 0.f)
            {
                return {};
            }

            const float inverseLength = 1.f / std::sqrt(lengthSquared);
            return {vector.x * inverseLength, vector.y * inverseLength};
        }
    }

    void PlayerController::Tick(Application& app, const float deltaTime)
    {
        Controller::Tick(app, deltaTime);

        Actor* pawn = GetPawn();
        if (pawn == nullptr || !pawn->IsActive())
        {
            return;
        }

        auto* movementComponent = pawn->GetComponent<MovementComponent>();
        if (movementComponent == nullptr)
        {
            return;
        }

        const auto& transform = pawn->GetTransform();
        const sf::Vector2f cursorPosition = app.GetWindow().GetMouseWorldPosition();

        if (const sf::Vector2f dir = cursorPosition - transform.GetPosition();
            dir.x != 0.f || dir.y != 0.f)
        {
            movementComponent->SetMaxSpeed(m_moveSpeed);
            movementComponent->AddInputVector(NormalizeOrZero(dir));
        }
    }
}
