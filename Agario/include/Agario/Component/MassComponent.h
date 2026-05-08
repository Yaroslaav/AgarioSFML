#pragma once

#include "Agario/Config/Settings.h"
#include "Engine/Components/ActorComponent.h"

namespace Agario
{
    class CircleActor;

    class MassComponent : public Engine::ActorComponent
    {
    public:
        explicit MassComponent(float startMass, float initialRadius, const ConsumeSettings& consumeSettings);

        void BeginPlay(Engine::Application& app) override;

        void AddMass(float amount);
        void SetMass(float amount);

        [[nodiscard]] float GetMass() const
        {
            return m_currentMass;
        }

        [[nodiscard]] bool CanConsume(float otherMass) const
        {
            return otherMass <= m_currentMass * m_consumeSettings.thresholdRatio;
        }

        [[nodiscard]] ConsumeSettings GetConsumeSettings() const
        {
            return m_consumeSettings;
        }

        void Reset();
        void RecalculateRadius() const
        {
            ApplyRadius();
        }
    private:
        void ApplyRadius() const;

        float m_initialMass = 0.f;
        float m_currentMass = 0.f;
        ConsumeSettings m_consumeSettings;
        CircleActor* m_ownerCircleActor = nullptr;
    };
}
