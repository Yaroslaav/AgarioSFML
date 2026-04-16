#include "Agario/World/Cell.h"

#include "Engine/Components/MovementComponent.h"

#include <algorithm>
#include <cmath>

namespace Agario
{
    Cell::Cell(const float radius, const sf::Color& color, const sf::Vector2f& startPosition, const float maxSpeed, const float startMass) :
        CircleActor(radius, color, startPosition),
        m_currentMass(startMass)
    {
        m_radiusPerRootMass = radius / std::sqrt(std::max(startMass, 0.01f));

        auto* movementComponent = AddComponent<Engine::MovementComponent>();
        movementComponent->SetMaxSpeed(maxSpeed);
    }

    void Cell::Grow(const float amount)
    {
        m_currentMass = std::max(0.01f, m_currentMass + amount);
        SetRadius(m_radiusPerRootMass * std::sqrt(m_currentMass));
    }
}
