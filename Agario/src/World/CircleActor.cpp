#include "Agario/World/CircleActor.h"

#include <algorithm>

#include "Engine/Components/SphereCollisionComponent.h"
#include "Engine/Core/Application.h"
#include "Engine/Math/MathUtils.h"

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
        transform.SetPosition(Engine::Math::ClampToRect(transform.GetPosition(), bounds, GetRadius()));
    }

    float CircleActor::GetRenderSortKey() const
    {
        return GetRadius();
    }

    float CircleActor::GetRadius() const
    {
        return m_shape.getRadius();
    }

    void CircleActor::SetRadius(float radius)
    {
        radius *= m_radiusMultiplier;
        m_shape.setRadius(radius);
        m_shape.setOrigin({radius, radius});
        m_collision->SetRadius(radius);
    }

    Engine::SphereCollisionComponent* CircleActor::GetCollision() const
    {
        return m_collision;
    }
}
