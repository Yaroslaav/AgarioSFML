#pragma once

#include "Engine/Config/Settings.h"
#include "Engine/World/Controller/Controller.h"

#include <SFML/System/Vector2.hpp>

namespace Engine
{
    class AIController : public Controller
    {
    public:
        AIController() = default;

        explicit AIController(const AIControllerSettings& settings);
        AIController(const AIControllerSettings& settings, Actor* pawn);

        void SetAcceptableRadius(const float acceptableRadius)
        {
            m_acceptableRadius = acceptableRadius;
        }

        [[nodiscard]] float GetAcceptableRadius() const
        {
            return m_acceptableRadius;
        }

    protected:
        [[nodiscard]] bool ReachedPosition(const sf::Vector2f& target) const;

        float m_acceptableRadius = 4.f;
    };
}
