#pragma once

#include "Engine/World/Actor.h"

#include <SFML/Graphics/CircleShape.hpp>

namespace Agario
{
    class CenterMarkerActor : public Engine::Actor
    {
    public:
        CenterMarkerActor();

        void Render(Engine::Application& app) override;

    private:
        sf::CircleShape m_shape;
    };
}
