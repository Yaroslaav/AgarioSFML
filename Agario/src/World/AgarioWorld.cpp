#include "Agario/World/AgarioWorld.h"

#include "Agario/Actors/Cell.h"
#include "Agario/Actors/Food.h"
#include "Engine/View/Window.h"

#include <algorithm>
#include <limits>

#include "Engine/Core/Application.h"

namespace Agario
{
    void AgarioWorld::Initialize(const WorldSettings& worldSettings, const ChunkSettings& chunkSettings)
    {
        SetBounds(worldSettings.bounds);
        m_chunkGrid.Initialize(worldSettings.bounds, chunkSettings);
    }

    void AgarioWorld::UpdateChunkGrid()
    {
        m_chunkGrid.ClearMass();

        for (Food* food : GetAllActorsOfClass<Food>())
        {
            if (food != nullptr && food->IsActive())
            {
                m_chunkGrid.AddFood(*food);
            }
        }

        for (const Cell* cell : GetAllActorsOfClass<Cell>())
        {
            if (cell != nullptr && cell->IsActive())
            {
                m_chunkGrid.AddCell(*cell);
            }
        }
    }

    void AgarioWorld::Render(Engine::Application &app) const
    {
        m_chunkGrid.Draw(app.GetWindow());

        World::Render(app);
    }

    void AgarioWorld::Tick(Engine::Application &app, const float deltaTime)
    {
        World::Tick(app, deltaTime);
        UpdateChunkGrid();
    }

    void AgarioWorld::BeginPlay(Engine::Application &app)
    {
        World::BeginPlay(app);
        UpdateChunkGrid();
    }
}
