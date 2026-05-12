#pragma once
#include <algorithm>
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
    inline float DistanceSquared(const sf::Vector2f a, const sf::Vector2f b)
    {
        const sf::Vector2f diff = a - b;
        return diff.x * diff.x + diff.y * diff.y;
    }

    inline float Distance(const sf::Vector2f a, const sf::Vector2f b)
    {
        return std::sqrt(DistanceSquared(a, b));
    }
    inline float LengthSquared(const sf::Vector2f a)
    {
        return a.x * a.x + a.y * a.y;
    }

    inline float Length(const sf::Vector2f a)
    {
        return std::sqrt(LengthSquared(a));
    }
    inline sf::Vector2f NormalizeOrZero(const sf::Vector2f vector)
    {
        const float lengthSquared = LengthSquared(vector);
        if (lengthSquared <= 0.f)
        {
            return {};
        }

        const float inverseLength = 1.f / std::sqrt(lengthSquared);
        return {vector.x * inverseLength, vector.y * inverseLength};
    }


    inline sf::Vector2f ForwardVector(const sf::Vector2f vector)
    {
        return NormalizeOrZero(vector);
    }
    inline sf::Vector2f ClampLength(const sf::Vector2f vector, const float maxLength)
    {
        if (maxLength <= 0.f)
        {
            return {};
        }

        const float lengthSquared = LengthSquared(vector);
        if (lengthSquared <= maxLength * maxLength)
        {
            return vector;
        }

        const float scale = maxLength / std::sqrt(lengthSquared);
        return {vector.x * scale, vector.y * scale};
    }

    inline sf::Vector2f MoveTowardZero(const sf::Vector2f vector, const float maxDelta)
    {
        const float length = Length(vector);
        if (length <= 0.f || maxDelta <= 0.f)
        {
            return vector;
        }

        const float newLength = std::max(0.f, length - maxDelta);
        if (newLength <= 0.f)
        {
            return {};
        }

        const float scale = newLength / length;
        return {vector.x * scale, vector.y * scale};
    }
}
