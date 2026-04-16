#pragma once

#include "Agario/World/CircleActor.h"

namespace Agario
{
    class Food final : public CircleActor
    {
    public:
        explicit Food(const sf::Vector2f& startPosition, float mass = 1.f);

        [[nodiscard]] float GetMass() const
        {
            return m_mass;
        }

    private:
        float m_mass = 0;
    };
}
