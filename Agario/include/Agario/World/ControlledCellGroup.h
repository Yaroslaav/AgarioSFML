#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector>

namespace Agario
{
    class Cell;

    class ControlledCellGroup
    {
    public:
        void Add(Cell& cell);
        void Remove(Cell& cell);

        void MoveToward(const sf::Vector2f& destination) const;
        void SplitAll();

        [[nodiscard]] Cell* GetFirstActiveCell() const;

        [[nodiscard]] const std::vector<Cell*>& GetCells() const
        {
            return m_cells;
        }

    private:
        std::vector<Cell*> m_cells;
    };
}
