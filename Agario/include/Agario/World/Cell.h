#pragma once

#include "Agario/Component/MassComponent.h"
#include "Agario/Config/Settings.h"
#include "Agario/World/CircleActor.h"
#include "Engine/Components/MovementComponent.h"

namespace Agario
{
    class Cell : public CircleActor
    {
    public:
        Cell(const sf::Color& color, const sf::Vector2f& startPosition, float maxSpeed, float startMass, const ConsumeSettings& consumeSettings, int teamId = -1);
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

        [[nodiscard]] bool CanSplit() const
        {
            return m_massComponent->CanSplit();
        }

        [[nodiscard]] int GetTeamId() const
        {
            return m_teamId;
        }

        void SetTeamId(const int teamId)
        {
            m_teamId = teamId;
        }

        Cell* Split();

        void Die(Actor& causer);
        Engine::Event<Actor*> OnDeath;

    private:
        MassComponent* m_massComponent = nullptr;
        Engine::MovementComponent* m_movementComponent = nullptr;
        int m_teamId = -1;
    };
}
