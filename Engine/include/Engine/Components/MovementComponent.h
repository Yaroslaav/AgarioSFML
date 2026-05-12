#pragma once

#include "Engine/Components/ActorComponent.h"

#include <SFML/System/Vector2.hpp>

namespace Engine
{
    class MovementComponent : public ActorComponent
    {
    public:
        void AddInputVector(const sf::Vector2f& input);

        void Tick(Application& app, float deltaTime) override;

        void SetVelocity(const sf::Vector2f& velocity);

        [[nodiscard]] const sf::Vector2f& GetVelocity() const;

        void Stop();

        void SetMaxSpeed(float maxSpeed);

        [[nodiscard]] float GetMaxSpeed() const;

        void SetAcceleration(float acceleration);

        [[nodiscard]] float GetAcceleration() const;

        void SetBrakingDeceleration(float brakingDeceleration);

        [[nodiscard]] float GetBrakingDeceleration() const;

    private:
        sf::Vector2f m_pendingInput{};
        sf::Vector2f m_velocity{};
        float m_maxSpeed = 250.f;
        float m_acceleration = 1400.f;
        float m_brakingDeceleration = 1800.f;
    };
}
