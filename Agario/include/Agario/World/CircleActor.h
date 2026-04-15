#pragma once

#include "Engine/Components/SphereCollisionComponent.h"
#include "Engine/World/Actor.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace Agario
{
    class CircleActor : public Engine::Actor
    {
    public:
        CircleActor(float radius, const sf::Color& color, const sf::Vector2f& startPosition);

        void Render(Engine::Application& app) override;
        void ConstrainToWorldBounds(const sf::FloatRect& bounds) override;
        [[nodiscard]] float GetRadius() const;
        [[nodiscard]] Engine::SphereCollisionComponent* GetCollision() const;

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
        Engine::SphereCollisionComponent* m_collision = nullptr;
    };
}
