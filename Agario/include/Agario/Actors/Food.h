#pragma once

#include "Agario/Config/Settings.h"
#include "Agario/Actors/CircleActor.h"

namespace Agario
{
    class Food final : public CircleActor
    {
    public:
        explicit Food(const FoodSettings& settings, const sf::Vector2f& startPosition);

        [[nodiscard]] float GetMass() const
        {
            return m_mass;
        }

    private:
        float m_mass = 0;
    };
}
