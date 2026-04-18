#pragma once
#include <complex>

#include "SFML/System/Vector2.hpp"

namespace Engine::Math
{
    inline bool IsNearlyZero(const float value, const float eps = 0.0001f)
    {
        return std::abs(value) <= eps;
    }

    inline bool IsNearlyZero(const sf::Vector2f value, const float eps = 0.0001f)
    {
        return std::abs(value.x) <= eps && std::abs(value.y) <= eps;
    }

    inline sf::Vector2f NormalizeOrZero(const sf::Vector2f vector)
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
