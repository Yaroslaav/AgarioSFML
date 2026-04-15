#include "Agario/World/Player/PlayerActor.h"

#include "Engine/Core/Application.h"

namespace Agario
{
    PlayerActor::PlayerActor()
    {
        m_shape.setRadius(30.f);
        m_shape.setOrigin({30.f, 30.f});
        GetTransform().SetPosition({640.f, 360.f});
    }

    void PlayerActor::Render(Engine::Application& app)
    {
        GetTransform().ApplyTo(m_shape);
        app.GetWindow().Draw(m_shape);
    }
}
