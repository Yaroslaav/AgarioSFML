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

    class DebugSystem
    {
    public:
        static void DrawLine(const sf::Vector2f& start, const sf::Vector2f& end, const sf::Color& color = sf::Color::Red, float thickness = 1.f);
        static void DrawCircle(const sf::Vector2f &center, float radius, const sf::Color &color = sf::Color::Red, float thickness = 1.f, int segments = 32);

        static void Render(Application& app);
        static void Clear();

        static bool IsDebugMode();
        static void SetDebugMode(bool enabled);
        static void ToggleDebugMode();

        static bool IsChunkDebugEnabled();
        static void ToggleChunkDebug();

        static bool IsDebugTracesEnabled();
        static void ToggleDebugTraces();

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
        
        static bool s_isDebugMode;
        static bool s_showChunkDebug;
        static bool s_showDebugTraces;
    };
}
