#include "Agario/World/ChunkGrid.h"

#include "Agario/Config/Settings.h"
#include "Agario/World/Cell.h"
#include "Agario/World/Food.h"
#include "Engine/View/Window.h"

#include <algorithm>
#include <cmath>

namespace Agario
{
    void ChunkGrid::Initialize(const sf::FloatRect& bounds, const ChunkSettings& settings)
    {
        m_bounds = bounds;
        m_gridColor = settings.gridColor;
        m_dummyFoodMassPerFood = settings.dummyFoodMassPerFood;
        m_dummyEnemyMassPerCell = settings.dummyEnemyMassPerCell;

        m_columns = std::max(1, settings.columns);
        m_rows = std::max(1, settings.rows);
        m_chunkSize = {
            m_bounds.size.x / static_cast<float>(m_columns),
            m_bounds.size.y / static_cast<float>(m_rows)
        };
        m_chunks.assign(static_cast<std::size_t>(m_columns * m_rows), {});

        RebuildGridLines();
    }

    void ChunkGrid::ClearMass()
    {
        for (ChunkData& chunk : m_chunks)
        {
            chunk.foodMass = 0.f;
            chunk.enemyMass = 0.f;
        }
    }

    void ChunkGrid::AddFood(const Food& food)
    {
        const int index = GetChunkIndex(food.GetActorPosition());
        if (index < 0)
        {
            return;
        }

        m_chunks[static_cast<std::size_t>(index)].foodMass += m_dummyFoodMassPerFood;
    }

    void ChunkGrid::AddCell(const Cell& cell)
    {
        const int index = GetChunkIndex(cell.GetActorPosition());
        if (index < 0)
        {
            return;
        }

        m_chunks[static_cast<std::size_t>(index)].enemyMass += m_dummyEnemyMassPerCell;
    }

    void ChunkGrid::Draw(Engine::Window& window) const
    {
        if (!IsInitialized())
        {
            return;
        }

        window.Draw(m_gridLines);
    }

    const ChunkData* ChunkGrid::GetChunkAt(const sf::Vector2f& worldPosition) const
    {
        const int index = GetChunkIndex(worldPosition);
        if (index < 0)
        {
            return nullptr;
        }

        return &m_chunks[static_cast<std::size_t>(index)];
    }

    int ChunkGrid::GetChunkIndex(const sf::Vector2f& worldPosition) const
    {
        if (!IsInitialized())
        {
            return -1;
        }

        if (!m_bounds.contains(worldPosition))
        {
            return -1;
        }

        const float localX = worldPosition.x - m_bounds.position.x;
        const float localY = worldPosition.y - m_bounds.position.y;

        const int column = std::clamp(static_cast<int>(localX / m_chunkSize.x), 0, m_columns - 1);
        const int row = std::clamp(static_cast<int>(localY / m_chunkSize.y), 0, m_rows - 1);
        return row * m_columns + column;
    }

    void ChunkGrid::RebuildGridLines()
    {
        m_gridLines.clear();

        const float left = m_bounds.position.x;
        const float top = m_bounds.position.y;
        const float right = m_bounds.position.x + m_bounds.size.x;
        const float bottom = m_bounds.position.y + m_bounds.size.y;

        for (int column = 0; column <= m_columns; ++column)
        {
            const float x = std::min(left + column * m_chunkSize.x, right);
            m_gridLines.append(sf::Vertex{{x, top}, m_gridColor});
            m_gridLines.append(sf::Vertex{{x, bottom}, m_gridColor});
        }

        for (int row = 0; row <= m_rows; ++row)
        {
            const float y = std::min(top + row * m_chunkSize.y, bottom);
            m_gridLines.append(sf::Vertex{{left, y}, m_gridColor});
            m_gridLines.append(sf::Vertex{{right, y}, m_gridColor});
        }
    }
}
