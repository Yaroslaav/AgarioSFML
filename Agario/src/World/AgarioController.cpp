#include "Agario/World/AgarioController.h"

#include "Agario/World/Cell.h"

namespace Agario
{
    AgarioController::AgarioController(Actor* pawn)
        : Controller(pawn)
    {
    }

    void AgarioController::Split()
    {
        m_controlledCells.SplitAll();
    }

    void AgarioController::SetAcceptableRadius(const float acceptableRadius)
    {
        m_acceptableRadius = acceptableRadius;
    }

    float AgarioController::GetAcceptableRadius() const
    {
        return m_acceptableRadius;
    }

    Cell* AgarioController::GetPrimaryCell() const
    {
        return m_controlledCells.GetFirstActiveCell();
    }

    void AgarioController::MoveControlledCellsToward(const sf::Vector2f& destination) const
    {
        m_controlledCells.MoveToward(destination);
    }

    bool AgarioController::ReachedPosition(const sf::Vector2f& target) const
    {
        const Cell* cell = GetPrimaryCell();
        if (cell == nullptr)
        {
            return false;
        }

        const sf::Vector2f delta = target - cell->GetActorPosition();
        const float distanceSquared = delta.x * delta.x + delta.y * delta.y;
        const float acceptableRadiusSquared = m_acceptableRadius * m_acceptableRadius;
        return distanceSquared < acceptableRadiusSquared;
    }

    void AgarioController::OnPossess(Actor& pawn)
    {
        if (auto* cell = dynamic_cast<Cell*>(&pawn))
        {
            m_controlledCells.Add(*cell);
            OnCellPossessed(*cell);
        }
    }

    void AgarioController::OnUnPossess()
    {
        if (auto* cell = GetPawn<Cell>())
        {
            OnCellUnPossessed(*cell);
            m_controlledCells.Remove(*cell);
        }
    }
}
