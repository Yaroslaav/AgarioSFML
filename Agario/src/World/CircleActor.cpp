#include "Agario/World/CircleActor.h"

#include <algorithm>

#include "Engine/Components/SphereCollisionComponent.h"
#include "Engine/Core/Application.h"

namespace Agario
{
    CircleActor::CircleActor(const float radius, const sf::Color& color, const sf::Vector2f& startPosition)
    {
        m_shape.setRadius(radius);
        m_shape.setOrigin({radius, radius});
        m_shape.setFillColor(color);
        GetTransform().SetPosition(startPosition);

        m_collision = AddComponent<Engine::SphereCollisionComponent>(radius);
    }

    void CircleActor::Render(Engine::Application& app)
    {
        GetTransform().ApplyTo(m_shape);
        app.GetWindow().Draw(m_shape);
    }

    void CircleActor::ConstrainToWorldBounds(const sf::FloatRect& bounds)
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

    float CircleActor::GetRadius() const
    {
        return m_shape.getRadius();
    }

    Engine::SphereCollisionComponent* CircleActor::GetCollision() const
    {
        return m_collision;
    }
}
