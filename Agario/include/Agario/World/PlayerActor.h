#pragma once

#include "Engine/World/Actor.h"

#include <SFML/Graphics/CircleShape.hpp>

namespace Agario
{
    class PlayerActor : public Engine::Actor
    {
    public:
        PlayerActor();

        void Tick(Engine::Application& app, float deltaTime) override;
        void Render(Engine::Application& app) override;

    private:
        sf::CircleShape m_shape;
        float m_speed = 250.f;
    };
}
