#pragma once

#include "Engine/Components/MovementComponent.h"
#include "Engine/World/Controller/Controller.h"

namespace Engine
{
    class PlayerController : public Controller
    {
    public:
        void Tick(Application& app, float deltaTime) override;
    };
}
