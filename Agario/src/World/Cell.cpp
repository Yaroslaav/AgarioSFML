#include "Agario/World/Cell.h"

#include "Engine/Components/MovementComponent.h"
#include "Engine/Core/Application.h"

namespace Agario
{
    Cell::Cell(const float radius, const sf::Color& color, const sf::Vector2f& startPosition)
    {
        m_shape.setRadius(radius);
        m_shape.setOrigin({radius, radius});
        m_shape.setFillColor(color);
        GetTransform().SetPosition(startPosition);
        AddComponent<Engine::MovementComponent>();
    }

    void Cell::Render(Engine::Application& app)
    {
        GetTransform().ApplyTo(m_shape);
        app.GetWindow().Draw(m_shape);
    }
}
