#include "Engine/World/Controller/AIController.h"

namespace Engine
{
    AIController::AIController(const AIControllerSettings& settings)
    {
        SetAcceptableRadius(settings.acceptableRadius);
    }

    AIController::AIController(const AIControllerSettings& settings, Actor* pawn)
        : Controller(pawn)
    {
        SetAcceptableRadius(settings.acceptableRadius);
    }

    bool AIController::ReachedPosition(const sf::Vector2f& target) const
    {
        const sf::Vector2f delta = target - GetPawn()->GetActorPosition();
        const float distanceSquared = delta.x * delta.x + delta.y * delta.y;
        const float acceptableRadiusSquared = m_acceptableRadius * m_acceptableRadius;
        return distanceSquared < acceptableRadiusSquared;
    }
}
