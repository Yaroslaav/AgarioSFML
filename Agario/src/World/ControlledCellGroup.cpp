#include "Agario/World/ControlledCellGroup.h"

#include "Agario/World/Cell.h"
#include "Engine/Components/MovementComponent.h"
#include "Engine/Math/MathUtils.h"

#include <algorithm>

namespace Agario
{
    void ControlledCellGroup::Add(Cell& cell)
    {
        if (std::find(m_cells.begin(), m_cells.end(), &cell) == m_cells.end())
        {
            m_cells.push_back(&cell);
        }
    }

    void ControlledCellGroup::Remove(Cell& cell)
    {
        m_cells.erase(std::remove(m_cells.begin(), m_cells.end(), &cell), m_cells.end());
    }

    void ControlledCellGroup::MoveToward(const sf::Vector2f& destination) const
    {
        for (Cell* cell : m_cells)
        {
            if (cell == nullptr || !cell->IsActive())
            {
                continue;
            }

            auto* movementComponent = cell->GetComponent<Engine::MovementComponent>();
            if (movementComponent == nullptr)
            {
                continue;
            }

            const sf::Vector2f direction = destination - cell->GetActorPosition();
            if (direction.x != 0.f || direction.y != 0.f)
            {
                movementComponent->AddInputVector(Engine::Math::NormalizeOrZero(direction));
            }
        }
    }

    void ControlledCellGroup::SplitAll()
    {
        const std::vector<Cell*> cellsToSplit = m_cells;

        for (Cell* cell : cellsToSplit)
        {
            if (cell == nullptr || !cell->IsActive())
            {
                continue;
            }

            if (Cell* splitCell = cell->Split())
            {
                Add(*splitCell);
            }
        }
    }

    Cell* ControlledCellGroup::GetFirstActiveCell() const
    {
        for (Cell* cell : m_cells)
        {
            if (cell != nullptr && cell->IsActive())
            {
                return cell;
            }
        }

        return nullptr;
    }
}
