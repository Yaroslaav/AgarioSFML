#pragma once

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

    private:
        Actor* m_owner = nullptr;
    };
}
