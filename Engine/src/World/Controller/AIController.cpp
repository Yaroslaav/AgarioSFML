#include "Engine/World/Controller/AIController.h"

#include <cmath>
#include <random>

#include "Engine/Core/Application.h"

namespace Engine
{
    namespace
    {
        constexpr float FullRotationRadians = 6.28318530718f; // PI * 2
    }

    AIController::AIController(const Agario::BotSettings &settings)
    {
        SetAcceptableRadius(settings.ai.acceptableRadius);
    }

    AIController::AIController(const Agario::BotSettings &settings, Actor *pawn)
        : Controller(pawn)
    {
        SetAcceptableRadius(settings.ai.acceptableRadius);
    }


    sf::Vector2f AIController::GetRandomLocationInRadius(const sf::Vector2f& center, float radius)
    {
        static std::mt19937 rng{std::random_device{}()};
        std::uniform_real_distribution<float> angleDistribution(0.f, FullRotationRadians);
        std::uniform_real_distribution<float> radiusDistribution(0.f, radius);

        const float angle = angleDistribution(rng);
        radius = radiusDistribution(rng);

        return {
            center.x + std::cos(angle) * radius,
            center.y + std::sin(angle) * radius
        };
    }

    bool AIController::ReachedPosition(const sf::Vector2f& target) const
    {
        const sf::Vector2f delta = target - GetPawn()->GetActorPosition();
        const float distanceSquared = delta.x * delta.x + delta.y * delta.y;
        const float acceptableRadiusSquared = m_acceptableRadius * m_acceptableRadius;
        return distanceSquared < acceptableRadiusSquared;
    }
}
