#pragma once

#include "Engine/Components/MovementComponent.h"
#include "Engine/World/Controller/Controller.h"

#include <SFML/System/Vector2.hpp>

namespace Engine
{
    class AIController : public Controller
    {
    public:
        void Tick(Application& app, float deltaTime) override;

        void SetRoamingRadius(const float roamingRadius)
        {
            m_roamingRadius = roamingRadius;
        }

        [[nodiscard]] float GetRoamingRadius() const
        {
            return m_roamingRadius;
        }

        void SetRetargetInterval(const float retargetInterval)
        {
            m_retargetInterval = retargetInterval;
        }

        [[nodiscard]] float GetRetargetInterval() const
        {
            return m_retargetInterval;
        }

        void SetAcceptableRadius(const float acceptableRadius)
        {
            m_acceptableRadius = acceptableRadius;
        }

        [[nodiscard]] float GetAcceptableRadius() const
        {
            return m_acceptableRadius;
        }

    private:
        void PickNewTarget(const sf::Vector2f& center);
        [[nodiscard]] bool HasReachedTarget(const sf::Vector2f& currentPosition) const;

        sf::Vector2f m_targetPosition{};
        float m_retargetTimer = 0.f;
        float m_roamingRadius = 220.f;
        float m_retargetInterval = 1.5f;
        float m_acceptableRadius = 4.f;
        bool m_hasTarget = false;
    };
}
