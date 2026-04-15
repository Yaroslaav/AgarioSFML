#pragma once

#include "Agario/World/CircleActor.h"

namespace Agario
{
    class Cell : public CircleActor
    {
    public:
        Cell(float radius, const sf::Color& color, const sf::Vector2f& startPosition, float maxSpeed = 250.f);
    };
}
