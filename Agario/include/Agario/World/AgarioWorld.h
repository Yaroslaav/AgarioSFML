#pragma once

#include "Agario/Config/Settings.h"
#include "Agario/World/ChunkGrid.h"
#include "Engine/World/World.h"

#include <optional>

namespace Engine
{
    class Window;
}

namespace Agario
{
    class Cell;

    class AgarioWorld : public Engine::World
    {
    public:
        void Initialize(const WorldSettings& worldSettings, const ChunkSettings& chunkSettings);
        void UpdateChunkGrid();

        void Render(Engine::Application &app) const override;

        void Tick(Engine::Application &app, float deltaTime) override;

        void BeginPlay(Engine::Application &app) override;

        [[nodiscard]] ChunkGrid& GetChunkGrid()
        {
            return m_chunkGrid;
        }

    private:
        ChunkGrid m_chunkGrid;
    };
}
