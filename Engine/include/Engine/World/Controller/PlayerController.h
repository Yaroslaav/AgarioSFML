#pragma once

#include "Engine/World/Controller/Controller.h"

namespace Engine
{
    class PlayerController : public Controller
    {
    public:
        void Tick(Application& app, float deltaTime) override;

        void SetMoveSpeed(const float moveSpeed)
        {
            m_moveSpeed = moveSpeed;
        }

        [[nodiscard]] float GetMoveSpeed() const
        {
            return m_moveSpeed;
        }

    private:
        float m_moveSpeed = 250.f;
    };
}
