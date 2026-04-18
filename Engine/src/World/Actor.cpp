#include "Engine/World/Actor.h"

#include "Engine/Core/Application.h"

namespace Engine
{
    Actor::Actor()
    {
        m_transformComponent.SetOwner(this);
    }

    void Actor::BeginPlay(Application& app)
    {
        m_transformComponent.BeginPlay(app);

        for (const auto& component : m_components)
        {
            component->BeginPlay(app);
        }
    }

    void Actor::EndPlay()
    {
        m_transformComponent.EndPlay();

        for (const auto& component : m_components)
        {
            component->EndPlay();
        }
    }

    void Actor::Tick(Application &app, const float deltaTime)
    {
        if (!m_isActive)
            return;

        m_transformComponent.Tick(app, deltaTime);

        for (const auto& component : m_components)
        {
            component->Tick(app, deltaTime);
        }
    }

    void Actor::Render(Application& app)
    {
    }

    void Actor::ConstrainToWorldBounds(const sf::FloatRect& bounds)
    {
    }

    float Actor::GetRenderSortKey() const
    {
        return 0.f;
    }
}
