#include "Agario/World/AgarioPlayerController.h"

#include <iostream>

#include "Agario/Config/Settings.h"
#include "Agario/GameplayTags/GameTags.h"
#include "Agario/World/Cell.h"
#include "Engine/Core/Application.h"
#include "Engine/View/Camera.h"
#include "Engine/World/World.h"

namespace Agario
{
    AgarioPlayerController::AgarioPlayerController(Actor* pawn)
        : AgarioController(pawn)
    {
    }

    void AgarioPlayerController::BeginPlay(Engine::Application &app)
    {
        AgarioController::BeginPlay(app);

        app.GetInput().AddNewBind(Settings.input.playerSplitKey, Tags::Agario::Ability_Split)
            .OnPressedOnce.AddListener([this]()
            {
                Split();
            });
    }

    void AgarioPlayerController::Tick(Engine::Application &app, const float deltaTime)
    {
        AgarioController::Tick(app, deltaTime);

        const sf::Vector2f cursorPosition = app.GetWindow().GetMouseWorldPosition();
        MoveControlledCellsToward(cursorPosition);
    }

    void AgarioPlayerController::OnCellPossessed(Cell& cell)
    {
        if (m_cellDeathEventHandles.find(&cell) != m_cellDeathEventHandles.end())
        {
            return;
        }

        Cell* cellPtr = &cell;
        const Engine::Event<Actor*>::EventHandle handle = cell.OnDeath.AddListener([this, cellPtr](Actor*)
        {
            RefocusCameraIfFocusedCellDied(*cellPtr);
        });
        m_cellDeathEventHandles.emplace(&cell, handle);
    }

    void AgarioPlayerController::OnCellUnPossessed(Cell& cell)
    {
        const auto it = m_cellDeathEventHandles.find(&cell);
        if (it == m_cellDeathEventHandles.end())
        {
            return;
        }

        cell.OnDeath.RemoveListener(it->second);
        m_cellDeathEventHandles.erase(it);
    }

    void AgarioPlayerController::RefocusCameraIfFocusedCellDied(const Cell& deadCell) const
    {
        Engine::World* world = GetWorld();
        if (world == nullptr)
        {
            return;
        }

        Engine::Camera* camera = world->GetActiveCamera();
        if (camera == nullptr)
        {
            return;
        }

        if (!camera->IsFocusedOn(deadCell))
        {
            return;
        }

        Cell* cell = GetPrimaryCell();
        if (cell == nullptr)
        {
            return;
        }

        camera->SetFocusActor(*cell);
    }
}
