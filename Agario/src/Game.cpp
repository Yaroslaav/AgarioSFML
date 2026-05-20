#include "Agario/Game.h"

#include "Agario/Actors/Cell.h"
#include "Agario/Actors/Food.h"
#include "Agario/Config/Settings.h"
#include "Agario/Controllers/AgarioPlayerController.h"
#include "Agario/Controllers/CellAIController.h"
#include "Agario/Gameplay/CollisionSystem.h"
#include "Engine/Core/Application.h"
#include "Engine/View/Camera.h"

#include <iostream>

namespace Agario
{
    void Game::OnInit(Engine::Application& app)
    {
        std::cout
            << "Controls:\n"
            << "  Move: mouse cursor\n"
            << "  Split: Space\n"
            << "  Toggle fullscreen: F11\n"
            << "  Zoom: = / -\n"
            << "  Toggle debug: F1\n"
            << "  Toggle chunk debug: Numpad1\n"
            << "  Toggle debug traces: Numpad2\n"
            << "  Quit: Escape\n";

        app.GetInput().AddNewBind(Settings.input.debugToggleKey, Engine::GameplayTag("Input.Action.DebugToggle"))
            .OnPressedOnce.AddListener([]() { Engine::DebugSystem::ToggleDebugMode(); });

        app.GetInput().AddNewBind(Settings.input.debugChunkToggleKey, Engine::GameplayTag("Input.Action.DebugChunkToggle"))
            .OnPressedOnce.AddListener([]() { Engine::DebugSystem::ToggleChunkDebug(); });

        app.GetInput().AddNewBind(Settings.input.debugTracesToggleKey, Engine::GameplayTag("Input.Action.DebugTracesToggle"))
            .OnPressedOnce.AddListener([]() { Engine::DebugSystem::ToggleDebugTraces(); });

        app.GetInput().AddNewBind(Settings.input.quitKey, Engine::GameplayTag("Input.Action.Quit"))
            .OnPressedOnce.AddListener([&app]() { app.Close(); });

        app.GetInput().AddNewBind(sf::Keyboard::Key::H, Engine::GameplayTag("Input.Action.Help"))
            .OnPressedOnce.AddListener([this]() { m_ui.ToggleHelp(); });

        m_ui.Initialize();

        m_world.Initialize(Settings.world, Settings.chunks);

        Cell* playerCell = m_world.SpawnActor<Cell>(
            Settings.player,
            Settings.player.spawnPosition,
            Settings.gameplay.consume,
            0,
            "player");

        for (int i = 0; i < Settings.bots.count; ++i)
        {
            auto* botCell = m_world.SpawnActor<Cell>(
                Settings.bots,
                m_world.GetRandomPositionInBounds(Settings.bots.spawnPadding),
                Settings.gameplay.consume,
                i + 1,
                "bot" + std::to_string(i + 1));

            m_world.SpawnActor<CellAIController>(Settings.bots, botCell);
        }

        for (int i = 0; i < Settings.food.count; ++i)
        {
            m_world.SpawnActor<Food>(
                Settings.food,
                m_world.GetRandomPositionInBounds(Settings.food.spawnPadding));
        }

        m_world.SpawnActor<AgarioPlayerController>(playerCell);
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

        CollisionSystem::Resolve(m_world);
    }

    void Game::OnRender(Engine::Application& app)
    {
        m_world.Render(app);
        m_ui.Render(app.GetWindow());
    }

    void Game::OnShutdown(Engine::Application& app)
    {
        m_world.EndPlay();
    }
}
