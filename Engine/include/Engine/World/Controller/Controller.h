#pragma once

#include "Engine/World/Actor.h"

namespace Engine
{
    class Controller : public Actor
    {
    public:
        Controller() = default;
        explicit Controller(Actor* pawn) : m_pendingPawn(pawn) {}

        void BeginPlay(Application& app) override
        {
            Actor::BeginPlay(app);

            if (m_pendingPawn)
            {
                Possess(*m_pendingPawn);
                m_pendingPawn = nullptr;
            }
        }

        void Possess(Actor& pawn)
        {
            if (m_pawn == &pawn) return;

            if (m_pawn)
            {
                UnPossess();
            }

            m_pawn = &pawn;
            OnPossess(pawn);
        }

        void UnPossess()
        {
            if (!m_pawn) return;

            OnUnPossess();
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

    protected:
        virtual void OnPossess(Actor& pawn) {}
        virtual void OnUnPossess() {}

        Actor* m_pendingPawn = nullptr;

    private:
        Actor* m_pawn = nullptr;
    };
}
