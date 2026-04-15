#include "Agario/World/PlayerActor.h"

#include "Engine/Core/Application.h"

namespace Agario
{
    PlayerActor::PlayerActor()
    {
        m_shape.setRadius(30.f);
        m_shape.setOrigin({30.f, 30.f});
        GetTransform().SetPosition({640.f, 360.f});
    }

    void PlayerActor::Tick(Engine::Application& app, const float deltaTime)
    {
        Engine::Actor::Tick(app, deltaTime);

        auto& transform = GetTransform();
        const sf::Vector2f cursorPosition = app.GetWindow().GetMouseWorldPosition();

        if (const sf::Vector2f dir = cursorPosition - transform.GetPosition();
            dir.x != 0.f || dir.y != 0.f)
        {
            transform.Move(dir.normalized() * m_speed * deltaTime);
        }
    }

    void PlayerActor::Render(Engine::Application& app)
    {
        GetTransform().ApplyTo(m_shape);
        app.GetWindow().Draw(m_shape);
    }
}
