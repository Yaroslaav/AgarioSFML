#include "Engine/Components/MovementComponent.h"

#include <algorithm>

#include "Engine/Math/MathUtils.h"
#include "Engine/World/Actor.h"

namespace Engine
{
    void MovementComponent::AddInputVector(const sf::Vector2f& input)
    {
        m_pendingInput.x += input.x;
        m_pendingInput.y += input.y;
    }

    void MovementComponent::Tick(Application& app, const float deltaTime)
    {
        ActorComponent::Tick(app, deltaTime);

        Actor* owner = GetOwner();
        if (owner == nullptr)
        {
            m_pendingInput = {};
            return;
        }

        if (!Math::IsNearlyZero(m_pendingInput) && m_acceleration > 0.f && deltaTime > 0.f)
        {
            const sf::Vector2f accelerationDirection = Math::NormalizeOrZero(m_pendingInput);
            const float speedDelta = m_acceleration * deltaTime;
            m_velocity.x += accelerationDirection.x * speedDelta;
            m_velocity.y += accelerationDirection.y * speedDelta;
        }
        else
        {
            m_velocity = Math::MoveTowardZero(m_velocity, m_brakingDeceleration * deltaTime);
        }

        m_velocity = Math::ClampLength(m_velocity, m_maxSpeed);

        if (!Math::IsNearlyZero(m_velocity) && deltaTime > 0.f)
        {
            owner->GetTransform().Move({m_velocity.x * deltaTime, m_velocity.y * deltaTime});
        }

        m_pendingInput = {};
    }

    void MovementComponent::SetVelocity(const sf::Vector2f& velocity)
    {
        m_velocity = Math::ClampLength(velocity, m_maxSpeed);
    }

    const sf::Vector2f& MovementComponent::GetVelocity() const
    {
        return m_velocity;
    }

    void MovementComponent::Stop()
    {
        m_velocity = {};
        m_pendingInput = {};
    }

    void MovementComponent::SetMaxSpeed(const float maxSpeed)
    {
        m_maxSpeed = std::max(0.f, maxSpeed);
        m_velocity = Math::ClampLength(m_velocity, m_maxSpeed);
    }

    float MovementComponent::GetMaxSpeed() const
    {
        return m_maxSpeed;
    }

    void MovementComponent::SetAcceleration(const float acceleration)
    {
        m_acceleration = std::max(0.f, acceleration);
    }

    float MovementComponent::GetAcceleration() const
    {
        return m_acceleration;
    }

    void MovementComponent::SetBrakingDeceleration(const float brakingDeceleration)
    {
        m_brakingDeceleration = std::max(0.f, brakingDeceleration);
    }

    float MovementComponent::GetBrakingDeceleration() const
    {
        return m_brakingDeceleration;
    }
}
