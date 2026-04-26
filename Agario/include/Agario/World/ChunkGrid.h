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
    };

    class ChunkGrid
    {
    public:
        void Initialize(const sf::FloatRect& bounds, const ChunkSettings& settings);
        void ClearMass();
        void AddFood(const Food& food);
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

    private:
        [[nodiscard]] int GetChunkIndex(const sf::Vector2f& worldPosition) const;
        void RebuildGridLines();

        sf::FloatRect m_bounds{};
        sf::Vector2f m_chunkSize{};
        sf::Color m_gridColor = sf::Color::Transparent;
        float m_dummyFoodMassPerFood = 1.f;
        float m_dummyEnemyMassPerCell = 1.f;
        int m_columns = 0;
        int m_rows = 0;
        std::vector<ChunkData> m_chunks;
        sf::VertexArray m_gridLines{sf::PrimitiveType::Lines};
        sf::Font m_tuffyFont;
    };
}
