#pragma once
#include "Engine/World/Actor.h"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/System/Vector2.hpp"

namespace Agario
{

    class Food : public Engine::Actor
    {
    public:
        explicit Food(const sf::Vector2f& startPosition);

        void Render(Engine::Application &app) override;

    private:
        sf::CircleShape m_shape;
    };
}
