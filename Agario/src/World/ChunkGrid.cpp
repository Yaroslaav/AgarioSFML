#include "Agario/World/ChunkGrid.h"

#include "Agario/Config/Settings.h"
#include "Agario/World/Cell.h"
#include "Agario/World/Food.h"
#include "Engine/View/Window.h"

#include <algorithm>
#include <cmath>
#include <filesystem>
#include <iostream>
#include <random>

#include "Engine/Core/DebugSystem.h"
#include "Engine/Math/MathUtils.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"

namespace Agario
{
    void ChunkGrid::Initialize(const sf::FloatRect& bounds, const ChunkSettings& settings)
    {
        m_bounds = bounds;
        m_gridColor = settings.gridColor;

        m_columns = std::max(1, settings.columns);
        m_rows = std::max(1, settings.rows);
        m_chunkSize = {
            m_bounds.size.x / static_cast<float>(m_columns),
            m_bounds.size.y / static_cast<float>(m_rows)
        };
        m_chunks.assign(m_columns * m_rows, {});

        RebuildGridLines();

         if (!m_tuffyFont.openFromFile("assets/Fonts/Tuffy/Tuffy-Regular.ttf"))
         {
             std::cout << "Failed to load font\n";
         }
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

        m_chunks[static_cast<std::size_t>(index)].foodMass += food.GetMass();
    }

    void ChunkGrid::AddCell(const Cell& cell)
    {
        const int index = GetChunkIndex(cell.GetActorPosition());
        if (index < 0)
        {
            return;
        }

        m_chunks[static_cast<std::size_t>(index)].enemyMass += cell.GetMass();
    }

    void ChunkGrid::Draw(Engine::Window& window) const
    {
        if (!IsInitialized())
        {
            return;
        }
        if (Engine::DebugSystem::IsDebugMode() && Engine::DebugSystem::IsChunkDebugEnabled())
        {
            const unsigned int characterSize = static_cast<unsigned int>(
                       std::clamp(std::min(m_chunkSize.x, m_chunkSize.y) * 0.22f, 10.f, 18.f));
            sf::Text text(m_tuffyFont, "", characterSize);
            text.setFillColor(sf::Color::White);

            for (int row = 0; row < m_rows; row++)
            {
                for (int col = 0; col < m_columns; col++)
                {
                    const ChunkData& chunk = m_chunks[row * m_columns + col];

                    std::ostringstream stream;
                    stream << std::setprecision(3) << "F: " << chunk.foodMass << "\nE: " << chunk.enemyMass;
                    text.setString(stream.str());

                    const sf::FloatRect localBounds = text.getLocalBounds();
                    text.setOrigin({
                        localBounds.position.x + localBounds.size.x * .5f,
                        localBounds.position.y + localBounds.size.y * .5f});

                    text.setPosition({GetChunkCenter(col, row)});
                    window.Draw(text);
                }
            }
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

    const ChunkData* ChunkGrid::GetChunkData(const int col, const int row) const
    {
        if (!IsInitialized() || col < 0 || col >= m_columns || row < 0 || row >= m_rows)
        {
            return nullptr;
        }

        return &m_chunks[row * m_columns + col];
    }

    sf::Vector2f ChunkGrid::GetChunkCenter(const int col, const int row) const
    {
        return {
            m_bounds.position.x + (static_cast<float>(col) + .5f) * m_chunkSize.x,
            m_bounds.position.y + (static_cast<float>(row) + .5f) * m_chunkSize.y};
    }

    sf::Vector2f ChunkGrid::GetBestFoodChunkPositionInRadius(const sf::Vector2f& center, const float radius) const
    {
        if (!IsInitialized())
        {
            return center;
        }

        const auto [startCol, startRow, endCol, endRow] = GetGridBounds(center, radius);

        float maxFood = -1.f;
        sf::Vector2f bestPos = center;
        const float radiusSq = radius * radius;

        for (int row = startRow; row <= endRow; ++row)
        {
            for (int col = startCol; col <= endCol; ++col)
            {
                const sf::Vector2f chunkCenter = GetChunkCenter(col, row);
                if (Engine::Math::DistanceSquared(chunkCenter, center) <= radiusSq)
                {
                    const int chunkIndex = row * m_columns + col;
                    if (m_chunks[chunkIndex].foodMass > maxFood)
                    {
                        maxFood = m_chunks[chunkIndex].foodMass;
                        bestPos = chunkCenter;
                    }
                }
            }
        }

        return bestPos;
    }

    sf::Vector2f ChunkGrid::GetRandomChunkPositionInRadius(const sf::Vector2f &center, float radius) const
    {
        if (!IsInitialized())
        {
            return center;
        }

        const auto [startCol, startRow, endCol, endRow] = GetGridBounds(center, radius);

        std::vector<sf::Vector2f> validPositions;
        const float radiusSq = radius * radius;

        for (int row = startRow; row <= endRow; ++row)
        {
            for (int col = startCol; col <= endCol; ++col)
            {
                const sf::Vector2f chunkCenter = GetChunkCenter(col, row);
                if (Engine::Math::DistanceSquared(chunkCenter, center) <= radiusSq)
                {
                    validPositions.push_back(chunkCenter);
                    Engine::DebugSystem::DrawCircle(chunkCenter, 10.f, sf::Color::Green, 1, 32, 1);
                }
            }
        }

        if (validPositions.empty())
        {
            return center;
        }

        static std::mt19937 rng{std::random_device{}()};
        std::uniform_int_distribution<std::size_t> dist(0, validPositions.size() - 1);
        return validPositions[dist(rng)];
    }

    GridBounds ChunkGrid::GetGridBounds(const sf::Vector2f& center, const float radius) const
    {
        return {
            WorldToGridX(center.x - radius),
            WorldToGridY(center.y - radius),
            WorldToGridX(center.x + radius),
            WorldToGridY(center.y + radius)
        };
    }

    int ChunkGrid::GetChunkIndex(const sf::Vector2f& worldPosition) const
    {
        if (!IsInitialized() || !m_bounds.contains(worldPosition))
        {
            return -1;
        }

        return WorldToGridY(worldPosition.y) * m_columns + WorldToGridX(worldPosition.x);
    }

    int ChunkGrid::WorldToGridX(const float x) const
    {
        return std::clamp(static_cast<int>((x - m_bounds.position.x) / m_chunkSize.x), 0, m_columns - 1);
    }

    int ChunkGrid::WorldToGridY(const float y) const
    {
        return std::clamp(static_cast<int>((y - m_bounds.position.y) / m_chunkSize.y), 0, m_rows - 1);
    }

    void ChunkGrid::AddGridLine(const sf::Vector2f start, const sf::Vector2f end)
    {
        m_gridLines.append(sf::Vertex{start, m_gridColor});
        m_gridLines.append(sf::Vertex{end, m_gridColor});
    }

    void ChunkGrid::RebuildGridLines()
    {
        m_gridLines.clear();

        const float left = m_bounds.position.x;
        const float top = m_bounds.position.y;
        const float right = m_bounds.position.x + m_bounds.size.x;
        const float bottom = m_bounds.position.y + m_bounds.size.y;

        for (int column = 0; column <= m_columns; column++)
        {
            const float x = std::min(left + column * m_chunkSize.x, right);
            AddGridLine({x, top}, {x, bottom});
        }

        for (int row = 0; row <= m_rows; row++)
        {
            const float y = std::min(top + row * m_chunkSize.y, bottom);
            AddGridLine({left, y}, {right, y});
        }
    }
}
