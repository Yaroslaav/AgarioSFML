#pragma once

#include "Engine/Core/IGame.h"
#include <SFML/Graphics/CircleShape.hpp>

namespace Agario
{
    class Game final : public Engine::IGame
    {
    public:
        void OnInit(Engine::Application& app) override;
        void OnEvent(Engine::Application& app) override;
        void OnUpdate(Engine::Application& app, float deltaTime) override;
        void OnRender(Engine::Application& app) override;
        void OnShutdown(Engine::Application& app) override;

    private:
        sf::CircleShape m_player;
        float m_speed = 250.f;
    };
}
