#include "Agario/Component/MassComponent.h"

#include "Agario/World/CircleActor.h"
#include "Engine/World/Actor.h"

#include <algorithm>
#include <cmath>

namespace Agario
{
    MassComponent::MassComponent(const float startMass, const float initialRadius, const ConsumeSettings& consumeSettings) :
        m_initialMass(std::max(startMass, 0.01f)),
        m_currentMass(m_initialMass),
        m_radiusPerRootMass(consumeSettings.radiusPerMass),
        m_consumeThresholdRatio(consumeSettings.thresholdRatio)
    {
    }

    void MassComponent::BeginPlay(Engine::Application& app)
    {
        ActorComponent::BeginPlay(app);
        m_ownerCircleActor = static_cast<CircleActor*>(GetOwner());
        ApplyRadius();
    }

    void MassComponent::AddMass(const float amount)
    {
        m_currentMass = std::max(0.01f, m_currentMass + amount);
        ApplyRadius();
    }

    void MassComponent::Reset()
    {
        m_currentMass = m_initialMass;
        ApplyRadius();
    }

    void MassComponent::ApplyRadius() const
    {
        if (m_ownerCircleActor == nullptr)
        {
            return;
        }

        m_ownerCircleActor->SetRadius(m_radiusPerRootMass * std::sqrt(m_currentMass));
    }
}
