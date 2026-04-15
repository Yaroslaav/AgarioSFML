#include "Engine/World/Controller/Controller.h"

namespace Engine
{
    sf::Vector2f Controller::NormalizeOrZero(const sf::Vector2f vector)
    {
        const float lengthSquared = vector.x * vector.x + vector.y * vector.y;
        if (lengthSquared <= 0.f)
        {
            return {};
        }

        const float inverseLength = 1.f / std::sqrt(lengthSquared);
        return {vector.x * inverseLength, vector.y * inverseLength};
    }
}