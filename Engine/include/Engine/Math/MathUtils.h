#pragma once
#include <cmath>

#include "SFML/System/Vector2.hpp"

namespace Engine::Math
{
    inline constexpr float PI = 3.14159265358979323846f;

    inline constexpr float RadiansToDegrees(const float radians)
    {
        return radians * 180.f / PI;
    }

    inline constexpr float DegreesToRadians(const float degrees)
    {
        return degrees * PI / 180.f;
    }

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

    inline float DistanceSquared(const sf::Vector2f a, const sf::Vector2f b)
    {
        const sf::Vector2f diff = a - b;
        return diff.x * diff.x + diff.y * diff.y;
    }

    inline float Distance(const sf::Vector2f a, const sf::Vector2f b)
    {
        return std::sqrt(DistanceSquared(a, b));
    }

    inline sf::Vector2f ForwardVector(const sf::Vector2f vector)
    {
        return NormalizeOrZero(vector);
    }
}
