#pragma once

#include <functional>
#include <vector>

#include "Engine/Components/ActorComponent.h"

#include <SFML/System/Vector2.hpp>

#include "Engine/Helpers/Event.h"

namespace Engine
{
    class SphereCollisionComponent : public ActorComponent
    {
    public:
        explicit SphereCollisionComponent(float radius = 0.f)
            : m_radius(radius)
        {
        }

        void SetRadius(const float radius)
        {
            m_radius = radius;
        }

        [[nodiscard]] float GetRadius() const
        {
            return m_radius;
        }

        void SetEnabled(const bool enabled)
        {
            m_enabled = enabled;
        }

        [[nodiscard]] bool IsEnabled() const
        {
            return m_enabled;
        }

        [[nodiscard]] sf::Vector2f GetWorldCenter() const;
        [[nodiscard]] bool Overlaps(const SphereCollisionComponent& other) const;
        [[nodiscard]] bool FullyCovers(const SphereCollisionComponent& other) const;
        [[nodiscard]] bool ContainsPoint(const sf::Vector2f& point) const;

        Event<Actor*, ActorComponent*> OnBeginOverlap;
        Event<Actor*, ActorComponent*> OnEndOverlapOverlap;

    private:
        float m_radius = 0.f;
        bool m_enabled = true;
    };
}
