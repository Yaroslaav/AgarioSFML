#include "Engine/Components/SphereCollisionComponent.h"

#include "Engine/Math/MathUtils.h"
#include "Engine/World/Actor.h"

namespace Engine
{
    sf::Vector2f SphereCollisionComponent::GetWorldCenter() const
    {
        if (const Actor* owner = GetOwner(); owner != nullptr)
        {
            return owner->GetActorPosition();
        }

        return {};
    }

    bool SphereCollisionComponent::Overlaps(const SphereCollisionComponent& other) const
    {
        if (!m_enabled || !other.m_enabled)
        {
            return false;
        }

        const sf::Vector2f delta = other.GetWorldCenter() - GetWorldCenter();
        const float distanceSquared = delta.x * delta.x + delta.y * delta.y;
        const float combinedRadius = m_radius + other.m_radius;
        return distanceSquared <= combinedRadius * combinedRadius;
    }

    bool SphereCollisionComponent::FullyCovers(const SphereCollisionComponent& other) const
    {
        if (!m_enabled || !other.m_enabled)
        {
            return false;
        }
        const sf::Vector2f delta = other.GetWorldCenter() - GetWorldCenter();
        return Math::Length(delta) + other.m_radius <= m_radius;
    }

    bool SphereCollisionComponent::ContainsPoint(const sf::Vector2f& point) const
    {
        if (!m_enabled)
        {
            return false;
        }

        const sf::Vector2f delta = point - GetWorldCenter();
        const float distanceSquared = delta.x * delta.x + delta.y * delta.y;
        return distanceSquared <= m_radius * m_radius;
    }
}
