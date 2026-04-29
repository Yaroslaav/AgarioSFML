#pragma once

#include "Agario/Component/MassComponent.h"
#include "Agario/Config/Settings.h"
#include "Agario/World/CircleActor.h"

namespace Agario
{
    class Cell : public CircleActor
    {
    public:
        Cell(float radiusPerMass, const sf::Color& color, const sf::Vector2f& startPosition, float maxSpeed, float startMass, const ConsumeSettings& consumeSettings, int teamId = -1);
        Cell(const PlayerSettings& settings, const sf::Vector2f& startPosition, const ConsumeSettings& consumeSettings, int teamId = -1);
        Cell(const BotSettings& settings, const sf::Vector2f& startPosition, const ConsumeSettings& consumeSettings, int teamId = -1);

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

        [[nodiscard]] int GetTeamId() const
        {
            return m_teamId;
        }

        void SetTeamId(const int teamId)
        {
            m_teamId = teamId;
        }

        void Die(Actor& causer);
        Engine::Event<Actor*> OnDeath;

    private:
        MassComponent* m_massComponent = nullptr;
        int m_teamId = -1;
    };
}
