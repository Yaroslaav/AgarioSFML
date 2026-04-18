#pragma once

#include "Engine/Components/MovementComponent.h"
#include "Engine/World/Controller/Controller.h"

#include <SFML/System/Vector2.hpp>

#include "../../../../../Agario/include/Agario/Config/Settings.h"

namespace Engine
{
    class AIController : public Controller
    {
    public:
        AIController() = default;

        explicit AIController(const Agario::BotSettings &settings);
        AIController(const Agario::BotSettings &settings, Actor* pawn);

        void SetAcceptableRadius(const float acceptableRadius)
        {
            m_acceptableRadius = acceptableRadius;
        }

        [[nodiscard]] float GetAcceptableRadius() const
        {
            return m_acceptableRadius;
        }

    protected:
        [[nodiscard]] sf::Vector2f GetRandomLocationInRadius(const sf::Vector2f &center, float radius);
        [[nodiscard]] bool ReachedPosition(const sf::Vector2f& target) const;

        float m_acceptableRadius = 4.f;
    };
}
