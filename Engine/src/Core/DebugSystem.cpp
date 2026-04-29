#include "Engine/Core/DebugSystem.h"
#include "Engine/Core/Application.h"
#include "Engine/View/Window.h"
#include "Engine/Math/MathUtils.h"
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <cmath>
#include <algorithm>

namespace Engine
{
    std::vector<DebugSystem::DebugLine> DebugSystem::s_lines;
    std::vector<DebugSystem::DebugCircle> DebugSystem::s_circles;
    
    bool DebugSystem::s_isDebugMode = false;
    bool DebugSystem::s_showChunkDebug = false;
    bool DebugSystem::s_showDebugTraces = false;

    void DebugSystem::DrawLine(const sf::Vector2f &start, const sf::Vector2f &end, const sf::Color &color, const float thickness, const float duration)
    {
        s_lines.push_back({start, end, color, thickness, duration});
    }

    void DebugSystem::DrawCircle(const sf::Vector2f& center, const float radius, const sf::Color& color, const float thickness, const int segments, const float duration)
    {
        s_circles.push_back({center, radius, color, segments, thickness, duration});
    }

    void DebugSystem::Render(Application& app, const float deltaTime)
    {
        if (!IsDebugMode() || !IsDebugTracesEnabled())
        {
            Clear();
            return;
        }

        Window& window = app.GetWindow();

        if (!s_lines.empty())
        {
            sf::VertexArray va(sf::PrimitiveType::Lines);
            for (auto& line : s_lines)
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

        UpdateDebugShapes(s_lines, deltaTime);
        UpdateDebugShapes(s_circles, deltaTime);
    }

    sf::RectangleShape DebugSystem::CreateRectangleShape(const DebugLine& line)
    {
        const sf::Vector2f direction = line.end - line.start;
        const float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        
        sf::RectangleShape shape({length, line.thickness});
        shape.setPosition(line.start);
        shape.setFillColor(line.color);
        shape.setOrigin({0.f, line.thickness / 2.f});
        
        shape.setRotation(sf::degrees(Math::RadiansToDegrees(std::atan2(direction.y, direction.x))));
        
        return shape;
    }

    sf::CircleShape DebugSystem::CreateCircleShape(const DebugCircle& circle)
    {
        sf::CircleShape shape(circle.radius, static_cast<std::size_t>(circle.segments));
        shape.setPosition(circle.center);
        shape.setOrigin({circle.radius, circle.radius});
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineColor(circle.color);
        shape.setOutlineThickness(circle.thickness);
        return shape;
    }

    void DebugSystem::Clear()
    {
        s_lines.clear();
        s_circles.clear();
    }

    bool DebugSystem::IsDebugMode()
    {
        return s_isDebugMode;
    }

    void DebugSystem::SetDebugMode(bool enabled)
    {
        s_isDebugMode = enabled;
    }

    void DebugSystem::ToggleDebugMode()
    {
        s_isDebugMode = !s_isDebugMode;
    }

    bool DebugSystem::IsChunkDebugEnabled()
    {
        return s_showChunkDebug;
    }

    void DebugSystem::ToggleChunkDebug()
    {
        s_showChunkDebug = !s_showChunkDebug;
    }

    bool DebugSystem::IsDebugTracesEnabled()
    {
        return s_showDebugTraces;
    }

    void DebugSystem::ToggleDebugTraces()
    {
        s_showDebugTraces = !s_showDebugTraces;
    }
    
    template<typename T>
    void DebugSystem::UpdateDebugShapes(T& shapes, float deltaTime)
    {
        auto updateRemainingTime = [deltaTime](auto& item) {
            if (item.remainingTime > 0.f)
            {
                item.remainingTime -= deltaTime;
                return item.remainingTime <= 0.f;
            }
            return item.remainingTime == 0.f;
        };
        shapes.erase(std::remove_if(shapes.begin(), shapes.end(), updateRemainingTime), shapes.end());
    }
}
