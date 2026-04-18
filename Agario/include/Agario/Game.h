#pragma once

#include "Engine/Core/IGame.h"
#include "Engine/World/World.h"
#include "Agario/World/ChunkGrid.h"

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

    private:
        void UpdateChunkGrid();
        
        Engine::World m_world;
        ChunkGrid m_chunkGrid;
    };
}
