#include "Engine/Core/DebugDraw.h"
#include "Engine/Core/Application.h"
#include "Engine/View/Window.h"
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <cmath>

namespace Engine
{
    std::vector<DebugDraw::DebugLine> DebugDraw::s_lines;
    std::vector<DebugDraw::DebugCircle> DebugDraw::s_circles;

    void DebugDraw::Line(const sf::Vector2f &start, const sf::Vector2f &end, const sf::Color &color, const float thickness)
    {
        s_lines.push_back({start, end, color, thickness});
    }

    void DebugDraw::Circle(const sf::Vector2f& center, const float radius, const sf::Color& color, const float thickness, const int segments)
    {
        s_circles.push_back({center, radius, color, segments, thickness});
    }

    void DebugDraw::Render(Application& app)
    {
        if (!app.IsDebugMode())
        {
            Clear();
            return;
        }

        Window& window = app.GetWindow();

        if (!s_lines.empty())
        {
            sf::VertexArray va(sf::PrimitiveType::Lines);
            for (const auto& line : s_lines)
            {
                if (line.thickness <= 1.01f)
                {
                    va.append(sf::Vertex{line.start, line.color});
                    va.append(sf::Vertex{line.end, line.color});
                }
                else
                {
                    window.Draw(CreateRectangleShape(line));
                }
            }
            if (va.getVertexCount() > 0)
            {
                window.Draw(va);
            }
        }

        for (const auto& circle : s_circles)
        {
            window.Draw(CreateCircleShape(circle));
        }

        Clear();
    }

    sf::RectangleShape DebugDraw::CreateRectangleShape(const DebugLine& line)
    {
        const sf::Vector2f direction = line.end - line.start;
        const float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        
        sf::RectangleShape shape({length, line.thickness});
        shape.setPosition(line.start);
        shape.setFillColor(line.color);
        shape.setOrigin({0.f, line.thickness / 2.f});
        
        shape.setRotation(sf::degrees(std::atan2(direction.y, direction.x) * 180.f / M_PI));
        
        return shape;
    }

    sf::CircleShape DebugDraw::CreateCircleShape(const DebugCircle& circle)
    {
        sf::CircleShape shape(circle.radius, static_cast<std::size_t>(circle.segments));
        shape.setPosition(circle.center);
        shape.setOrigin({circle.radius, circle.radius});
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineColor(circle.color);
        shape.setOutlineThickness(circle.thickness);
        return shape;
    }

    void DebugDraw::Clear()
    {
        s_lines.clear();
        s_circles.clear();
    }
}
