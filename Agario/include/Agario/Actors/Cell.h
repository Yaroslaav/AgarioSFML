#pragma once

#include "Agario/Components/MassComponent.h"
#include "Agario/Config/Settings.h"
#include "Agario/Actors/CircleActor.h"
#include "Engine/Components/MovementComponent.h"

#include <string>

namespace Agario
{
    class Cell : public CircleActor
    {
    public:
        Cell(const sf::Color& color, const sf::Vector2f& startPosition, float maxSpeed, float startMass, const ConsumeSettings& consumeSettings, int teamId = -1, std::string nickname = "");
        Cell(const PlayerSettings& settings, const sf::Vector2f& startPosition, const ConsumeSettings& consumeSettings, int teamId = -1, std::string nickname = "");
        Cell(const BotSettings& settings, const sf::Vector2f& startPosition, const ConsumeSettings& consumeSettings, int teamId = -1, std::string nickname = "");

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

        [[nodiscard]] bool CanMerge() const
        {
            return m_splitMergeTimer <= 0.f;
        }

        [[nodiscard]] float GetMergeProgress() const;

        [[nodiscard]] int GetTeamId() const
        {
            return m_teamId;
        }

        [[nodiscard]] const std::string& GetNickname() const
        {
            return m_nickname;
        }

        void SetTeamId(const int teamId)
        {
            m_teamId = teamId;
        }

        Cell* Split();

        void Tick(Engine::Application& app, float deltaTime) override;
        void Render(Engine::Application& app) override;
        void Die(Actor& causer);
        Engine::Event<Actor*> OnDeath;

    private:
        void StartSplitMergeTimer(float mergeDelay);

        MassComponent* m_massComponent = nullptr;
        Engine::MovementComponent* m_movementComponent = nullptr;
        std::string m_nickname;
        int m_teamId = -1;
        float m_splitMergeTimer = 0.f;
        float m_splitMergeDelay = 0.f;
    };
}
