#pragma once

#include "Engine/Components/ActorComponent.h"

namespace Agario
{
    class CircleActor;

    class MassComponent : public Engine::ActorComponent
    {
    public:
        explicit MassComponent(float startMass, float initialRadius, float consumeThresholdRatio);

        void BeginPlay(Engine::Application& app) override;

        void AddMass(float amount);

        [[nodiscard]] float GetMass() const
        {
            return m_currentMass;
        }

        [[nodiscard]] bool CanConsume(float otherMass) const
        {
            return otherMass <= m_currentMass * m_consumeThresholdRatio;
        }

        void Reset();

    private:
        void ApplyRadius() const;

        float m_initialMass = 0.f;
        float m_currentMass = 0.f;
        float m_radiusPerRootMass = 0.f;
        float m_consumeThresholdRatio = 0.8f;
        CircleActor* m_ownerCircleActor = nullptr;
    };
}
