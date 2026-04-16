#pragma once

#include "Agario/World/CircleActor.h"

namespace Agario
{
    class Cell : public CircleActor
    {
    public:
        Cell(float radius, const sf::Color& color, const sf::Vector2f& startPosition, float maxSpeed = 250.f, float startMass = 5);

        void Grow(float amount);
        [[nodiscard]] float GetMass() const
        {
            return m_currentMass;
        }

    private:
        float m_currentMass = 0;
        float m_radiusPerRootMass = 0;
    };
}
