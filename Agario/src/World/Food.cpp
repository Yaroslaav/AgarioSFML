#include "Agario/World/Food.h"

namespace Agario
{
    Food::Food(const sf::Vector2f& startPosition)
        : CircleActor(2.f, sf::Color(255, 210, 70), startPosition)
    {
    }
}
