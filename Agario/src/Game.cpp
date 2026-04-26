#include "Agario/Game.h"

#include "Agario/Config/Settings.h"
#include "Agario/World/Cell.h"
#include "Agario/World/Food.h"
#include "Engine/Core/Application.h"
#include "Engine/View/Camera.h"
#include "Engine/World/Controller/AIController.h"
#include "Engine/World/Controller/PlayerController.h"

#include "Agario/World/CellAIController.h"

namespace Agario
{
    void Game::OnInit(Engine::Application& app)
    {
        m_world.Initialize(Settings.world, Settings.chunks);

        Cell* playerCell = m_world.SpawnActor<Cell>(
            Settings.player,
            Settings.player.spawnPosition,
            Settings.gameplay.consume.thresholdRatio);

        for (int i = 0; i < Settings.bots.count; ++i)
        {
            auto* botCell = m_world.SpawnActor<Cell>(
                Settings.bots,
                m_world.GetRandomPositionInBounds(Settings.bots.spawnPadding),
                Settings.gameplay.consume.thresholdRatio);

            m_world.SpawnActor<CellAIController>(Settings.bots, botCell);
        }

        for (int i = 0; i < Settings.food.count; ++i)
        {
            m_world.SpawnActor<Food>(
                Settings.food,
                m_world.GetRandomPositionInBounds(Settings.food.spawnPadding));
        }

        auto* playerController = m_world.SpawnActor<Engine::PlayerController>();
        playerController->Possess(*playerCell);
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
            auto* playerCollision = player->GetCollision();

            for (auto* foodCell : food)
            {
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
                Cell* largerPlayer = player;
                Cell* smallerPlayer = otherPlayer;

                if (otherPlayer->GetMass() > player->GetMass())
                {
                    largerPlayer = otherPlayer;
                    smallerPlayer = player;
                }

                if (!largerPlayer->CanConsume(*smallerPlayer))
                {
                    continue;
                }

                auto* largerCollision = largerPlayer->GetCollision();
                auto* smallerCollision = smallerPlayer->GetCollision();
                if (!largerCollision->FullyCovers(*smallerCollision))
                {
                    continue;
                }

                largerPlayer->Grow(smallerPlayer->GetMass() * Settings.gameplay.consume.massGainFactor);
                smallerPlayer->GetTransform().SetPosition(m_world.GetRandomPositionInBounds(smallerPlayer->GetRadius()));
                smallerPlayer->ResetMass();
                smallerCollision->OnBeginOverlap.Broadcast(largerPlayer, largerCollision);
                largerCollision->OnBeginOverlap.Broadcast(smallerPlayer, smallerCollision);
            }
        }
    }
}
