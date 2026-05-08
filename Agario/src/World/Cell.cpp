#include "Agario/World/Cell.h"

#include "Agario/World/AgarioWorld.h"
#include "Engine/Components/MovementComponent.h"
#include <cmath>

namespace Agario
{
    Cell::Cell(const PlayerSettings& settings, const sf::Vector2f& startPosition, const ConsumeSettings& consumeSettings, const int teamId)
        : Cell(settings.color, startPosition, settings.maxSpeed, settings.startMass, consumeSettings, teamId)
    {
    }

    Cell::Cell(const BotSettings& settings, const sf::Vector2f& startPosition, const ConsumeSettings& consumeSettings, const int teamId)
        : Cell(settings.color, startPosition, settings.maxSpeed, settings.startMass, consumeSettings, teamId)
    {
    }

    Cell::Cell(const sf::Color& color, const sf::Vector2f& startPosition, const float maxSpeed,
               const float startMass, const ConsumeSettings& consumeSettings, const int teamId) :
        CircleActor(0.f, color, startPosition),
        m_teamId(teamId)
    {
        m_movementComponent = AddComponent<Engine::MovementComponent>();
        m_movementComponent->SetMaxSpeed(maxSpeed);

        const float calculatedRadius = std::sqrt(startMass) * consumeSettings.radiusPerMass;
        m_massComponent = AddComponent<MassComponent>(startMass, calculatedRadius, consumeSettings);
    }

    void Cell::Grow(const float amount)
    {
        m_massComponent->AddMass(amount);
    }

    Cell* Cell::Split()
    {
        float newMass = m_massComponent->GetMass() / 2;
        m_massComponent->SetMass(newMass);
        return GetWorld<AgarioWorld>()->SpawnActor<Cell>(
            m_shape.getFillColor(),
            GetTransform().GetPosition(),
            m_movementComponent->GetMaxSpeed(),
            newMass,
            m_massComponent->GetConsumeSettings(),
            m_teamId);
    }

    void Cell::Die(Actor &causer)
    {
        bool isLastActiveCellInGroup = true;
        if (m_teamId != -1)
        {
            const auto& cells = GetWorld<AgarioWorld>()->GetAllActorsOfClass<Cell>();
            int activeCellsInGroup = 0;

            for (const Cell* cell : cells)
            {
                if (cell != nullptr && cell->IsActive() && cell->GetTeamId() == m_teamId)
                {
                    ++activeCellsInGroup;
                }
            }

            isLastActiveCellInGroup = activeCellsInGroup <= 1;
        }

        if (isLastActiveCellInGroup)
        {
            ResetMass();
            GetTransform().SetPosition(GetWorld<AgarioWorld>()->GetRandomPositionInBounds(GetRadius()));
        }
        else
        {
            SetActive(false);
        }

        OnDeath.Broadcast(&causer);
    }
}
