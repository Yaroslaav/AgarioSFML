#include "Agario/Actors/Cell.h"

#include "Agario/World/AgarioWorld.h"
#include "Engine/Core/Application.h"
#include "Engine/Components/MovementComponent.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <utility>

namespace Agario
{
    const sf::Font* GetNicknameFont()
    {
        static sf::Font font;
        static const bool loaded = font.openFromFile("assets/Fonts/Tuffy/Tuffy-Bold.ttf");
        static bool reportedFailure = false;

        if (!loaded && !reportedFailure)
        {
            std::cout << "Failed to load nickname font\n";
            reportedFailure = true;
        }

        return loaded ? &font : nullptr;
    }

    Cell::Cell(const PlayerSettings& settings, const sf::Vector2f& startPosition, const ConsumeSettings& consumeSettings, const int teamId, std::string nickname)
        : Cell(settings.color, startPosition, settings.maxSpeed, settings.startMass, consumeSettings, teamId, std::move(nickname))
    {
    }

    Cell::Cell(const BotSettings& settings, const sf::Vector2f& startPosition, const ConsumeSettings& consumeSettings, const int teamId, std::string nickname)
        : Cell(settings.color, startPosition, settings.maxSpeed, settings.startMass, consumeSettings, teamId, std::move(nickname))
    {
    }

    Cell::Cell(const sf::Color& color, const sf::Vector2f& startPosition, const float maxSpeed,
               const float startMass, const ConsumeSettings& consumeSettings, const int teamId, std::string nickname) :
        CircleActor(0.f, color, startPosition),
        m_nickname(std::move(nickname)),
        m_teamId(teamId)
    {
        m_movementComponent = AddComponent<Engine::MovementComponent>();
        m_movementComponent->SetMaxSpeed(maxSpeed);

        m_massComponent = AddComponent<MassComponent>(startMass, consumeSettings);
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
            m_teamId,
            m_nickname);
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

    void Cell::Render(Engine::Application& app)
    {
        CircleActor::Render(app);

        if (m_nickname.empty())
        {
            return;
        }

        const sf::Font* font = GetNicknameFont();
        if (font == nullptr)
        {
            return;
        }

        const unsigned int characterSize = static_cast<unsigned int>(std::clamp(GetRadius() * 0.45f, 12.f, 28.f));
        sf::Text text(*font, m_nickname, characterSize);
        text.setFillColor(sf::Color::White);
        text.setOutlineColor(sf::Color(0, 0, 0, 180));
        text.setOutlineThickness(2.f);

        const sf::FloatRect localBounds = text.getLocalBounds();
        text.setOrigin({
            localBounds.position.x + localBounds.size.x * 0.5f,
            localBounds.position.y + localBounds.size.y * 0.5f
        });
        text.setPosition(GetActorPosition());

        app.GetWindow().Draw(text);
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

            isLastActiveCellInGroup = activeCellsInGroup <= 0;
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
