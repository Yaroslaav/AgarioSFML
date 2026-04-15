#include "../../include/Engine/World/Controller/PlayerController.h"

#include "Engine/Core/Application.h"

namespace Engine
{
    void PlayerController::Tick(Application& app, const float deltaTime)
    {
        Controller::Tick(app, deltaTime);

        Actor* pawn = GetPawn();
        if (pawn == nullptr || !pawn->IsActive())
        {
            return;
        }

        auto& transform = pawn->GetTransform();
        const sf::Vector2f cursorPosition = app.GetWindow().GetMouseWorldPosition();

        if (const sf::Vector2f dir = cursorPosition - transform.GetPosition();
            dir.x != 0.f || dir.y != 0.f)
        {
            transform.Move(dir.normalized() * m_moveSpeed * deltaTime);
        }
    }
}
