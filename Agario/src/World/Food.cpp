#include "Agario/World/Food.h"

#include "Engine/Core/Application.h"

namespace Agario
{
    Food::Food(const sf::Vector2f& startPosition)
    {
        m_shape.setRadius(2.f);
        m_shape.setOrigin({2.f, 2.f});
        m_shape.setFillColor(sf::Color(255, 210, 70));
        GetTransform().SetPosition(startPosition);
    }

    void Food::Render(Engine::Application &app)
    {
        GetTransform().ApplyTo(m_shape);
        app.GetWindow().Draw(m_shape);
    }
}
