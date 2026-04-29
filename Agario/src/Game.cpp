#include "Agario/Game.h"

#include "Agario/Config/Settings.h"
#include "Agario/World/Cell.h"
#include "Agario/World/Food.h"
#include "Engine/Core/Application.h"
#include "Engine/Math/MathUtils.h"
#include "Engine/View/Camera.h"
#include "Engine/World/Controller/AIController.h"
#include "Engine/World/Controller/PlayerController.h"

#include "Agario/World/CellAIController.h"

namespace Agario
{
    void Game::OnInit(Engine::Application& app)
    {
        app.GetInput().AddNewBind(Settings.input.debugToggleKey, Engine::GameplayTag("Input.Action.DebugToggle"))
            .OnPressedOnce.AddListener([]() { Engine::DebugSystem::ToggleDebugMode(); });

        app.GetInput().AddNewBind(Settings.input.debugChunkToggleKey, Engine::GameplayTag("Input.Action.DebugChunkToggle"))
            .OnPressedOnce.AddListener([]() { Engine::DebugSystem::ToggleChunkDebug(); });

        app.GetInput().AddNewBind(Settings.input.debugTracesToggleKey, Engine::GameplayTag("Input.Action.DebugTracesToggle"))
            .OnPressedOnce.AddListener([]() { Engine::DebugSystem::ToggleDebugTraces(); });

        app.GetInput().AddNewBind(Settings.input.quitKey, Engine::GameplayTag("Input.Action.Quit"))
            .OnPressedOnce.AddListener([&app]() { app.Close(); });

        m_world.Initialize(Settings.world, Settings.chunks);

        Cell* playerCell = m_world.SpawnActor<Cell>(
            Settings.player,
            Settings.player.spawnPosition,
            Settings.gameplay.consume,
            0);

        for (int i = 0; i < Settings.bots.count; ++i)
        {
            auto* botCell = m_world.SpawnActor<Cell>(
                Settings.bots,
                m_world.GetRandomPositionInBounds(Settings.bots.spawnPadding),
                Settings.gameplay.consume,
                i+1);

            m_world.SpawnActor<CellAIController>(Settings.bots, botCell);
        }

        for (int i = 0; i < Settings.food.count; ++i)
        {
            m_world.SpawnActor<Food>(
                Settings.food,
                m_world.GetRandomPositionInBounds(Settings.food.spawnPadding));
        }

        auto* playerController = m_world.SpawnActor<Engine::PlayerController>(playerCell);
        auto* camera = m_world.SpawnActor<Engine::Camera>(
            Settings.player.spawnPosition,
            static_cast<sf::Vector2f>(app.GetWindow().GetSize()));
        camera->SetFocusActor(*playerCell);
        m_world.SetActiveCamera(camera);
        m_world.BeginPlay(app);
    }

    void Game::OnEvent(Engine::Application& app)
    {
        auto& window = app.GetWindow();

        while (const auto event = window.PollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                app.Close();
            }
        }
    }

    void Game::OnUpdate(Engine::Application& app, const float deltaTime)
    {
        m_world.Tick(app, deltaTime);

        CheckCollision();
    }

    void Game::OnRender(Engine::Application& app)
    {
        m_world.Render(app);
    }

    void Game::OnShutdown(Engine::Application& app)
    {
        m_world.EndPlay();
    }

    void Game::CheckCollision()
    {
        const auto& players = m_world.GetAllActorsOfClass<Cell>();
        const auto& food = m_world.GetAllActorsOfClass<Food>();

        for (std::size_t playerIndex = 0; playerIndex < players.size(); ++playerIndex)
        {
            Cell* player = players[playerIndex];
            if (!player->IsActive()) continue;

            auto* playerCollision = player->GetCollision();

            for (auto* foodCell : food)
            {
                if (!foodCell->IsActive()) continue;

                auto* foodCellCollision = foodCell->GetCollision();
                if (playerCollision->FullyCovers(*foodCellCollision))
                {
                    player->Grow(foodCell->GetMass());
                    foodCell->GetTransform().SetPosition(m_world.GetRandomPositionInBounds(foodCell->GetRadius()));
                    foodCellCollision->OnBeginOverlap.Broadcast(player, playerCollision);
                    playerCollision->OnBeginOverlap.Broadcast(foodCell, foodCellCollision);
                }
            }

            for (std::size_t otherPlayerIndex = playerIndex + 1; otherPlayerIndex < players.size(); ++otherPlayerIndex)
            {
                Cell* otherPlayer = players[otherPlayerIndex];
                if (!otherPlayer->IsActive()) continue;

                if (player->GetTeamId() != -1 && player->GetTeamId() == otherPlayer->GetTeamId())
                {
                    ResolveTeamCollision(player, otherPlayer);
                }
                else
                {
                    ResolveEnemyCollision(player, otherPlayer);
                }
            }
        }
    }

    void Game::ResolveTeamCollision(Cell* cellA, Cell* cellB)
    {
        const sf::Vector2f centerA = cellA->GetCollision()->GetWorldCenter();
        const sf::Vector2f centerB = cellB->GetCollision()->GetWorldCenter();

        const float minDistance = cellA->GetRadius() + cellB->GetRadius();
        const float distSq = Engine::Math::DistanceSquared(centerA, centerB);

        if (distSq < minDistance * minDistance && distSq > 0.f)
        {
            const float dist = std::sqrt(distSq);
            const sf::Vector2f normal = (centerA - centerB) / dist;
            const sf::Vector2f separation = normal * ((minDistance - dist) * .5f);

            cellA->GetTransform().Move(separation);
            cellB->GetTransform().Move(-separation);
        }
    }

    void Game::ResolveEnemyCollision(Cell* cellA, Cell* cellB)
    {
        Cell* largerPlayer = cellA;
        Cell* smallerPlayer = cellB;

        if (cellB->GetMass() > cellA->GetMass())
        {
            largerPlayer = cellB;
            smallerPlayer = cellA;
        }

        if (!largerPlayer->CanConsume(*smallerPlayer))
        {
            return;
        }

        auto* largerCollision = largerPlayer->GetCollision();
        auto* smallerCollision = smallerPlayer->GetCollision();
        if (!largerCollision->FullyCovers(*smallerCollision))
        {
            return;
        }

        largerPlayer->Grow(smallerPlayer->GetMass() * Settings.gameplay.consume.massGainFactor);
        smallerPlayer->Die(*largerPlayer);
        largerCollision->OnBeginOverlap.Broadcast(smallerPlayer, smallerCollision);
    }
}
