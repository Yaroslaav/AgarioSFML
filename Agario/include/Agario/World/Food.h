#pragma once

#include "Agario/World/CircleActor.h"

namespace Agario
{
    class Food final : public CircleActor
    {
    public:
        explicit Food(const sf::Vector2f& startPosition);
    };
}
