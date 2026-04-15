#include "Agario/Game.h"

#include "Agario/World/CenterMarkerActor.h"
#include "Agario/World/PlayerActor.h"
#include "Engine/Core/Application.h"
#include "Engine/View/Camera.h"

#include <optional>

namespace Agario
{
    void Game::OnInit(Engine::Application& app)
    {
        auto* player = m_world.SpawnActor<PlayerActor>();
        m_world.SpawnActor<CenterMarkerActor>();
        auto* camera = m_world.SpawnActor<Engine::Camera>(
            sf::Vector2f(640.f, 360.f),
            static_cast<sf::Vector2f>(app.GetWindow().GetSize()));
        camera->SetFocusActor(*player);
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
