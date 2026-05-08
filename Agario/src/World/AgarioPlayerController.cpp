#include "Agario/World/AgarioPlayerController.h"

#include <iostream>

#include "Agario/Config/Settings.h"
#include "Agario/GameplayTags/GameTags.h"
#include "Agario/World/Cell.h"
#include "Engine/Core/Application.h"

namespace Agario
{
    AgarioPlayerController::AgarioPlayerController(Actor* pawn)
        : AgarioController(pawn)
    {
    }

    void AgarioPlayerController::BeginPlay(Engine::Application &app)
    {
        AgarioController::BeginPlay(app);

        std::cout << "split";
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
}
