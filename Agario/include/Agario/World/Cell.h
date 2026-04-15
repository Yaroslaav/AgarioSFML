#pragma once

#include "Engine/World/Actor.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>

namespace Agario
{
    class Cell : public Engine::Actor
    {
    public:
        Cell(float radius, const sf::Color& color, const sf::Vector2f& startPosition, float maxSpeed = 250.f);

        void Render(Engine::Application& app) override;
        void ConstrainToWorldBounds(const sf::FloatRect& bounds) override;
        [[nodiscard]] float GetRadius() const;

    protected:
        sf::CircleShape& GetShape()
        {
            return m_shape;
        }

        const sf::CircleShape& GetShape() const
        {
            return m_shape;
        }

    private:
        sf::CircleShape m_shape;
    };
}
