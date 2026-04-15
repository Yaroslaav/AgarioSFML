#include "Agario/World/CenterMarkerActor.h"

#include "Engine/Core/Application.h"

namespace Agario
{
    CenterMarkerActor::CenterMarkerActor()
    {
        m_shape.setRadius(10.f);
        m_shape.setOrigin({10.f, 10.f});
        GetTransform().SetPosition({640.f, 360.f});
    }

    void CenterMarkerActor::Render(Engine::Application& app)
    {
        GetTransform().ApplyTo(m_shape);
        app.GetWindow().Draw(m_shape);
    }
}
