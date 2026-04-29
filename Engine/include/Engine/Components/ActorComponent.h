#pragma once

#include <typeindex>

namespace Engine
{
    class Actor;
    class Application;

    class ActorComponent
    {
    public:
        virtual ~ActorComponent() = default;

        void SetOwner(Actor* owner)
        {
            m_owner = owner;
        }

        [[nodiscard]] Actor* GetOwner() const
        {
            return m_owner;
        }

        virtual void BeginPlay(Application& app) {}
        virtual void EndPlay() {}
        virtual void Tick(Application& app, float deltaTime) {}

        template<typename T>
        [[nodiscard]] bool IsA() const
        {
            return std::type_index(typeid(*this)) == std::type_index(typeid(T));
        }

    private:
        Actor* m_owner = nullptr;
    };
}
