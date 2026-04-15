#include "Agario/World/Cell.h"

#include <algorithm>

#include "Engine/Components/MovementComponent.h"
#include "Engine/Core/Application.h"

namespace Agario
{
    Cell::Cell(const float radius, const sf::Color& color, const sf::Vector2f& startPosition, const float maxSpeed)
    {
        m_shape.setRadius(radius);
        m_shape.setOrigin({radius, radius});
        m_shape.setFillColor(color);
        GetTransform().SetPosition(startPosition);
        auto* movementComponent = AddComponent<Engine::MovementComponent>();
        movementComponent->SetMaxSpeed(maxSpeed);
    }

    void Cell::Render(Engine::Application& app)
    {
        GetTransform().ApplyTo(m_shape);
        app.GetWindow().Draw(m_shape);
    }

    void Cell::ConstrainToWorldBounds(const sf::FloatRect& bounds)
    {
        auto& transform = GetTransform();
        const float minX = bounds.position.x + GetRadius();
        const float minY = bounds.position.y + GetRadius();
        const float maxX = bounds.position.x + bounds.size.x - GetRadius();
        const float maxY = bounds.position.y + bounds.size.y - GetRadius();

        const sf::Vector2f position = transform.GetPosition();
        transform.SetPosition({
            std::clamp(position.x, minX, maxX),
            std::clamp(position.y, minY, maxY)
        });
    }

    float Cell::GetRadius() const
    {
        return m_shape.getRadius();
    }
}
