#include "Agario/World/Cell.h"

#include "Engine/Components/MovementComponent.h"

namespace Agario
{
    Cell::Cell(const PlayerSettings& settings, const sf::Vector2f& startPosition, const float consumeThresholdRatio)
        : Cell(settings.radius, settings.color, startPosition, settings.maxSpeed, settings.startMass, consumeThresholdRatio)
    {
    }

    Cell::Cell(const BotSettings& settings, const sf::Vector2f& startPosition, const float consumeThresholdRatio)
        : Cell(settings.radius, settings.color, startPosition, settings.maxSpeed, settings.startMass, consumeThresholdRatio)
    {
    }

    Cell::Cell(const float radius, const sf::Color& color, const sf::Vector2f& startPosition, const float maxSpeed,
        const float startMass, const float consumeThresholdRatio) :
        CircleActor(radius, color, startPosition)
    {
        auto* movementComponent = AddComponent<Engine::MovementComponent>();
        movementComponent->SetMaxSpeed(maxSpeed);

        m_massComponent = AddComponent<MassComponent>(startMass, radius, consumeThresholdRatio);
    }

    void Cell::Grow(const float amount)
    {
        m_massComponent->AddMass(amount);
    }
}
