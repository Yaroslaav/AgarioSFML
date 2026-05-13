#include "Agario/World/Cell.h"

#include "Agario/World/AgarioWorld.h"
#include "Engine/Core/Application.h"
#include "Engine/Components/MovementComponent.h"
#include <algorithm>
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

    float Cell::GetMergeProgress() const
    {
        if (m_splitMergeDelay <= 0.f)
        {
            return 1.f;
        }

        return 1.f - std::clamp(m_splitMergeTimer / m_splitMergeDelay, 0.f, 1.f);
    }

    Cell* Cell::Split()
    {
        if (!CanSplit())
        {
            return nullptr;
        }

        const float newMass = m_massComponent->GetMass() / 2.f;
        const ConsumeSettings consumeSettings = m_massComponent->GetConsumeSettings();
        m_massComponent->SetMass(newMass);
        StartSplitMergeTimer(consumeSettings.splitMergeDelay);

        Cell* splitCell = GetWorld<AgarioWorld>()->SpawnActor<Cell>(
            m_shape.getFillColor(),
            GetTransform().GetPosition(),
            m_movementComponent->GetMaxSpeed(),
            newMass,
            consumeSettings,
            m_teamId);
        splitCell->StartSplitMergeTimer(consumeSettings.splitMergeDelay);
        return splitCell;
    }

    void Cell::Tick(Engine::Application& app, const float deltaTime)
    {
        CircleActor::Tick(app, deltaTime);

        if (m_splitMergeTimer > 0.f)
        {
            m_splitMergeTimer = std::max(0.f, m_splitMergeTimer - deltaTime);
        }
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
                if (cell != nullptr && cell != this && cell->IsActive() && cell->GetTeamId() == m_teamId)
                {
                    ++activeCellsInGroup;
                }
            }

            isLastActiveCellInGroup = activeCellsInGroup <= 1;
        }

        if (isLastActiveCellInGroup)
        {
            ResetMass();
            m_movementComponent->Stop();
            GetTransform().SetPosition(GetWorld<AgarioWorld>()->GetRandomPositionInBounds(GetRadius()));
        }
        else
        {
            m_movementComponent->Stop();
            SetActive(false);
        }

        OnDeath.Broadcast(&causer);
    }

    void Cell::StartSplitMergeTimer(const float mergeDelay)
    {
        m_splitMergeDelay = std::max(0.f, mergeDelay);
        m_splitMergeTimer = m_splitMergeDelay;
    }
}
