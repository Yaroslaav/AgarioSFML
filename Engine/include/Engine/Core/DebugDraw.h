#pragma once

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

namespace Engine
{
    class Window;
    class Application;

    class DebugDraw
    {
    public:
        static void Line(const sf::Vector2f& start, const sf::Vector2f& end, const sf::Color& color = sf::Color::Red, float thickness = 1.f);
        static void Circle(const sf::Vector2f &center, float radius, const sf::Color &color = sf::Color::Red, float thickness = 1.f, int segments = 32);

        static void Render(Application& app);
        static void Clear();

    private:
        struct DebugLine
        {
            sf::Vector2f start;
            sf::Vector2f end;
            sf::Color color;
            float thickness;
        };

        struct DebugCircle
        {
            sf::Vector2f center;
            float radius;
            sf::Color color;
            int segments;
            float thickness;
        };

        static sf::RectangleShape CreateRectangleShape(const DebugLine& line);
        static sf::CircleShape CreateCircleShape(const DebugCircle& circle);

        static std::vector<DebugLine> s_lines;
        static std::vector<DebugCircle> s_circles;
    };
}
