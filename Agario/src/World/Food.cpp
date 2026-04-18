#include "Agario/World/Food.h"

namespace Agario
{
    Food::Food(const FoodSettings& settings, const sf::Vector2f& startPosition)
        : CircleActor(settings.radius, settings.color, startPosition),
          m_mass(settings.mass)
    {
    }
}
