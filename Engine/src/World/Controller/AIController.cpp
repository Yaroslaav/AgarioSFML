#include "Engine/World/Controller/AIController.h"

#include <cmath>
#include <random>

#include "Engine/Core/Application.h"

namespace Engine
{
    namespace
    {
        constexpr float FullRotationRadians = 6.28318530718f;
    }

    void AIController::Tick(Application& app, const float deltaTime)
    {
        Controller::Tick(app, deltaTime);

        Actor* pawn = GetPawn();
        if (pawn == nullptr || !pawn->IsActive())
        {
            m_hasTarget = false;
            return;
        }

        auto* movementComponent = pawn->GetComponent<MovementComponent>();
        if (movementComponent == nullptr)
        {
            return;
        }

        const sf::Vector2f pawnPosition = pawn->GetActorPosition();

        m_retargetTimer -= deltaTime;
        if (!m_hasTarget || m_retargetTimer <= 0.f)
        {
            PickNewTarget(pawnPosition);
        }

        if (HasReachedTarget(pawnPosition))
        {
            PickNewTarget(pawnPosition);
            return;
        }

        movementComponent->AddInputVector(NormalizeOrZero(m_targetPosition - pawnPosition));
    }

    void AIController::PickNewTarget(const sf::Vector2f& center)
    {
        static std::mt19937 rng{std::random_device{}()};
        std::uniform_real_distribution<float> angleDistribution(0.f, FullRotationRadians);
        std::uniform_real_distribution<float> radiusDistribution(0.f, m_roamingRadius);

        const float angle = angleDistribution(rng);
        const float radius = radiusDistribution(rng);

        m_targetPosition = {
            center.x + std::cos(angle) * radius,
            center.y + std::sin(angle) * radius
        };
        m_retargetTimer = m_retargetInterval;
        m_hasTarget = true;
    }

    bool AIController::HasReachedTarget(const sf::Vector2f& currentPosition) const
    {
        const sf::Vector2f delta = m_targetPosition - currentPosition;
        const float distanceSquared = delta.x * delta.x + delta.y * delta.y;
        const float acceptableRadiusSquared = m_acceptableRadius * m_acceptableRadius;
        return distanceSquared < acceptableRadiusSquared;
    }
}
