#include "Engine/Components/MovementComponent.h"

#include <cmath>

#include "Engine/World/Actor.h"

namespace Engine
{
    namespace
    {
        sf::Vector2f NormalizeOrZero(const sf::Vector2f vector)
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

    void MovementComponent::Tick(Application& app, const float deltaTime)
    {
        ActorComponent::Tick(app, deltaTime);

        Actor* owner = GetOwner();
        if (owner == nullptr)
        {
            m_pendingInput = {};
            return;
        }

        if (m_pendingInput.x != 0.f || m_pendingInput.y != 0.f)
        {
            const sf::Vector2f direction = NormalizeOrZero(m_pendingInput);
            owner->GetTransform().Move({direction.x * m_maxSpeed * deltaTime, direction.y * m_maxSpeed * deltaTime});
        }

        m_pendingInput = {};
    }
}
