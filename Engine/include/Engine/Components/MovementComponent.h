#pragma once

#include "Engine/Components/ActorComponent.h"

#include <SFML/System/Vector2.hpp>

namespace Engine
{
    class MovementComponent : public ActorComponent
    {
    public:
        void AddInputVector(const sf::Vector2f& input)
        {
            m_pendingInput.x += input.x;
            m_pendingInput.y += input.y;
        }

        void Tick(Application& app, float deltaTime) override;

        void SetMaxSpeed(const float maxSpeed)
        {
            m_maxSpeed = maxSpeed;
        }

        [[nodiscard]] float GetMaxSpeed() const
        {
            return m_maxSpeed;
        }

    private:
        sf::Vector2f m_pendingInput{};
        float m_maxSpeed = 250.f;
    };
}
