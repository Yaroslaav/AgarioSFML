#pragma once
#include "Agario/World/AgarioController.h"
#include "Engine/Helpers/Event.h"

#include <unordered_map>

namespace Agario
{
    class Cell;

    class AgarioPlayerController : public AgarioController
    {
    public:
        AgarioPlayerController(Actor* pawn);

        void BeginPlay(Engine::Application &app) override;
        void Tick(Engine::Application &app, float deltaTime) override;

    protected:
        void OnCellPossessed(Cell& cell) override;
        void OnCellUnPossessed(Cell& cell) override;

    private:
        void RefocusCameraIfFocusedCellDied(const Cell& deadCell) const;

        std::unordered_map<Cell*, Engine::Event<Actor*>::EventHandle> m_cellDeathEventHandles;
    };
}
