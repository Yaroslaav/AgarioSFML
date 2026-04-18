#pragma once

#include "Agario/Component/MassComponent.h"
#include "Agario/Config/Settings.h"
#include "Agario/World/CircleActor.h"

namespace Agario
{
    class Cell : public CircleActor
    {
    public:
        Cell(float radius, const sf::Color& color, const sf::Vector2f& startPosition, float maxSpeed, float startMass, float consumeThresholdRatio);
        Cell(const PlayerSettings& settings, const sf::Vector2f& startPosition, float consumeThresholdRatio);
        Cell(const BotSettings& settings, const sf::Vector2f& startPosition, float consumeThresholdRatio);

        void Grow(float amount);
        [[nodiscard]] float GetMass() const
        {
            return m_massComponent->GetMass();
        }
        void ResetMass()
        {
            m_massComponent->Reset();
        }

        [[nodiscard]] bool CanConsume(const Cell& other) const
        {
            return m_massComponent->CanConsume(other.GetMass());
        }

    private:
        MassComponent* m_massComponent = nullptr;
    };
}
