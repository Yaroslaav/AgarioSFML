#pragma once

#include "Engine/World/Actor.h"

namespace Engine
{
    class Controller : public Actor
    {
    public:
        void Possess(Actor& pawn)
        {
            m_pawn = &pawn;
        }

        void UnPossess()
        {
            m_pawn = nullptr;
        }

        [[nodiscard]] Actor* GetPawn() const
        {
            return m_pawn;
        }

        template<typename T>
        T* GetPawn() const
        {
            static_assert(std::is_base_of_v<Actor, T>, "T must derive from Actor");
            return dynamic_cast<T*>(m_pawn);
        }

    private:
        Actor* m_pawn = nullptr;
    };
}
