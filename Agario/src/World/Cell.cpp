#include "Agario/World/Cell.h"

#include "Agario/World/AgarioWorld.h"
#include "Engine/Components/MovementComponent.h"
#include <cmath>

namespace Agario
{
    Cell::Cell(const PlayerSettings& settings, const sf::Vector2f& startPosition, const ConsumeSettings& consumeSettings, const int teamId)
        : Cell(consumeSettings.radiusPerMass, settings.color, startPosition, settings.maxSpeed, settings.startMass, consumeSettings, teamId)
    {
    }

    Cell::Cell(const BotSettings& settings, const sf::Vector2f& startPosition, const ConsumeSettings& consumeSettings, const int teamId)
        : Cell(consumeSettings.radiusPerMass, settings.color, startPosition, settings.maxSpeed, settings.startMass, consumeSettings, teamId)
    {
    }

    Cell::Cell(const float radiusPerMass, const sf::Color& color, const sf::Vector2f& startPosition, const float maxSpeed,
        const float startMass, const ConsumeSettings& consumeSettings, const int teamId) :
        CircleActor(0.f, color, startPosition),
        m_teamId(teamId)
    {
        auto* movementComponent = AddComponent<Engine::MovementComponent>();
        movementComponent->SetMaxSpeed(maxSpeed);

        const float calculatedRadius = std::sqrt(startMass) * radiusPerMass;
        m_massComponent = AddComponent<MassComponent>(startMass, calculatedRadius, consumeSettings);
    }

    void Cell::Grow(const float amount)
    {
        m_massComponent->AddMass(amount);
    }

    void Cell::Die(Actor &causer)
    {
        ResetMass();
        GetTransform().SetPosition(GetWorld<AgarioWorld>()->GetRandomPositionInBounds(GetRadius()));
        OnDeath.Broadcast(&causer);
    }
}
