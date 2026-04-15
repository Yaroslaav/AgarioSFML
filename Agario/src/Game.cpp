#include "Agario/Game.h"

#include "Agario/World/Cell.h"
#include "Agario/World/CenterMarkerActor.h"
#include "Engine/Core/Application.h"
#include "Engine/View/Camera.h"
#include "Engine/World/Controller/AIController.h"
#include "Engine/World/Controller/PlayerController.h"

#include <optional>

namespace Agario
{
    void Game::OnInit(Engine::Application& app)
    {
        auto* playerCell = m_world.SpawnActor<Cell>(30.f, sf::Color::White, sf::Vector2f(640.f, 360.f));
        auto* botCell = m_world.SpawnActor<Cell>(24.f, sf::Color(120, 220, 120), sf::Vector2f(860.f, 360.f), 180.f);
        m_world.SpawnActor<CenterMarkerActor>();

        auto* playerController = m_world.SpawnActor<Engine::PlayerController>();
        playerController->Possess(*playerCell);

        auto* aiController = m_world.SpawnActor<Engine::AIController>();
        aiController->Possess(*botCell);

        auto* camera = m_world.SpawnActor<Engine::Camera>(
            sf::Vector2f(640.f, 360.f),
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
    }

    void Game::OnRender(Engine::Application& app)
    {
        m_world.Render(app);
    }

    void Game::OnShutdown(Engine::Application& app)
    {
        m_world.EndPlay();
    }
}
