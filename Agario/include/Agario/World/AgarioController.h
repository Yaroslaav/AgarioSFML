#pragma once

#include "Agario/World/ControlledCellGroup.h"
#include "Engine/World/Controller/Controller.h"

#include <SFML/System/Vector2.hpp>

namespace Agario
{
    class Cell;

    class AgarioController : public Engine::Controller
    {
    public:
        AgarioController() = default;
        explicit AgarioController(Actor* pawn);

        void Split();

        void SetAcceptableRadius(float acceptableRadius);
        [[nodiscard]] float GetAcceptableRadius() const;

    protected:
        [[nodiscard]] Cell* GetPrimaryCell() const;
        void MoveControlledCellsToward(const sf::Vector2f& destination) const;
        [[nodiscard]] bool ReachedPosition(const sf::Vector2f& target) const;

        void OnPossess(Actor& pawn) override;
        void OnUnPossess() override;

        virtual void OnCellPossessed(Cell& cell) {}
        virtual void OnCellUnPossessed(Cell& cell) {}

    private:
        ControlledCellGroup m_controlledCells;
        float m_acceptableRadius = 4.f;
    };
}
