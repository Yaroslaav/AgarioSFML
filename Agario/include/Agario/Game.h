#pragma once

#include "Engine/Core/IGame.h"
#include "Agario/World/AgarioWorld.h"

namespace Agario
{
    class Game final : public Engine::IGame
    {
    public:
        void OnInit(Engine::Application& app) override;
        void OnEvent(Engine::Application& app) override;
        void OnUpdate(Engine::Application& app, float deltaTime) override;
        void OnRender(Engine::Application& app) override;
        void OnShutdown(Engine::Application& app) override;

        void CheckCollision();
        void ResolveTeamCollision(Cell* cellA, Cell* cellB);
        void ResolveEnemyCollision(Cell* cellA, Cell* cellB);

    private:
        AgarioWorld m_world;
    };
}
