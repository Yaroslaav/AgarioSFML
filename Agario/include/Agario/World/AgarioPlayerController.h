#pragma once
#include "Agario/World/AgarioController.h"

namespace Agario
{
    class Cell;

    class AgarioPlayerController : public AgarioController
    {
    public:
        AgarioPlayerController(Actor* pawn);

        void BeginPlay(Engine::Application &app) override;
        void Tick(Engine::Application &app, float deltaTime) override;
    };
}
