#include "Agario/Game.h"

#include "Agario/World/Cell.h"
#include "Agario/World/Food.h"
#include "Engine/Core/Application.h"
#include "Engine/View/Camera.h"
#include "Engine/World/Controller/AIController.h"
#include "Engine/World/Controller/PlayerController.h"

#include <random>
#include <optional>

namespace Agario
{
    void Game::OnInit(Engine::Application& app)
    {
        const sf::FloatRect worldBounds{{0.f, 0.f}, {2000.f, 2000.f}};
        m_world.SetBounds(worldBounds);

        auto* playerCell = m_world.SpawnActor<Cell>(30.f, sf::Color::White, sf::Vector2f(640.f, 360.f));
        auto* botCell = m_world.SpawnActor<Cell>(24.f, sf::Color(120, 220, 120), sf::Vector2f(860.f, 360.f), 180.f);
        
        std::mt19937 rng{std::random_device{}()};
        std::uniform_real_distribution<float> xDistribution(worldBounds.position.x + 12.f,
                                                            worldBounds.position.x + worldBounds.size.x - 12.f);
        std::uniform_real_distribution<float> yDistribution(worldBounds.position.y + 12.f,
                                                            worldBounds.position.y + worldBounds.size.y - 12.f);

        for (int i = 0; i < 200; ++i)
        {
            m_world.SpawnActor<Food>(sf::Vector2f{xDistribution(rng), yDistribution(rng)});
        }

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
