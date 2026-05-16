#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

#include "SFML/Graphics/Font.hpp"

namespace Engine
{
    class Window;
}

namespace Agario
{
    class Cell;
    class Food;
    struct ChunkSettings;

    struct ChunkData
    {
        float foodMass = 0.f;
        float enemyMass = 0.f;
        std::vector<Food*> foodActors;
    };

    struct GridBounds
    {
        int startCol;
        int startRow;
        int endCol;
        int endRow;
    };

    class ChunkGrid
    {
    public:
        void Initialize(const sf::FloatRect& bounds, const ChunkSettings& settings);
        void ClearMass();
        void AddFood(Food& food);
        void AddCell(const Cell& cell);
        void Draw(Engine::Window& window) const;

        [[nodiscard]] const ChunkData* GetChunkAt(const sf::Vector2f& worldPosition) const;
        [[nodiscard]] const ChunkData* GetChunkData(int col, int row) const;
        [[nodiscard]] bool IsInitialized() const
        {
            return m_columns > 0 && m_rows > 0;
        }

        [[nodiscard]] int GetColumns() const
        {
            return m_columns;
        }

        [[nodiscard]] int GetRows() const
        {
            return m_rows;
        }

        [[nodiscard]] sf::Vector2f GetChunkCenter(int col, int row) const;
        [[nodiscard]] sf::Vector2f GetBestFoodChunkPositionInRadius(const sf::Vector2f& center, float radius) const;
        [[nodiscard]] sf::Vector2f GetRandomChunkPositionInRadius(const sf::Vector2f& center, float radius) const;

        template<typename TCallback>
        void ForEachFoodInRadius(const sf::Vector2f& center, const float radius, TCallback&& callback) const
        {
            if (!IsInitialized())
            {
                return;
            }

            const auto [startCol, startRow, endCol, endRow] = GetGridBounds(center, radius);
            for (int row = startRow; row <= endRow; ++row)
            {
                const int rowOffset = row * m_columns;
                for (int col = startCol; col <= endCol; ++col)
                {
                    const ChunkData& chunk = m_chunks[rowOffset + col];
                    for (Food* food : chunk.foodActors)
                    {
                        callback(food);
                    }
                }
            }
        }

    private:
        [[nodiscard]] GridBounds GetGridBounds(const sf::Vector2f& center, float radius) const;
        [[nodiscard]] int WorldToGridX(float x) const;
        [[nodiscard]] int WorldToGridY(float y) const;
        [[nodiscard]] int GetChunkIndex(const sf::Vector2f& worldPosition) const;
        void AddGridLine(sf::Vector2f start, sf::Vector2f end);
        void RebuildGridLines();

        sf::FloatRect m_bounds{};
        sf::Vector2f m_chunkSize{};
        sf::Color m_gridColor = sf::Color::Transparent;

        int m_columns = 0;
        int m_rows = 0;

        std::vector<ChunkData> m_chunks;
        sf::VertexArray m_gridLines{sf::PrimitiveType::Lines};
        sf::Font m_tuffyFont;
    };
}
