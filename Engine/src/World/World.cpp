#include "Engine/World/World.h"

#include "Engine/Core/Application.h"
#include "Engine/View/Camera.h"

namespace Engine
{
    void World::BeginPlay(Application& app)
    {
        FlushPendingActors();

        for (const auto& actor : m_actors)
        {
            actor->BeginPlay(app);
        }

        SyncActiveCamera(app);
    }

    void World::EndPlay()
    {
        for (const auto& actor : m_actors)
        {
            actor->EndPlay();
        }

        m_pendingActors.clear();
        m_actors.clear();
        m_activeCamera = nullptr;
    }

    void World::Tick(Application& app, const float deltaTime)
    {
        FlushPendingActors();

        for (const auto& actor : m_actors)
        {
            actor->Tick(app, deltaTime);
        }

        ConstrainActorsToBounds();
        SyncActiveCamera(app);
    }

    void World::Render(Application& app) const
    {
        for (const auto& actor : m_actors)
        {
            if (!actor->IsActive())
            {
                continue;
            }

            actor->Render(app);
        }
    }

    void World::FlushPendingActors()
    {
        if (m_pendingActors.empty())
        {
            return;
        }

        for (auto& actor : m_pendingActors)
        {
            m_actors.push_back(std::move(actor));
        }

        m_pendingActors.clear();
    }

    void World::SetActiveCamera(Camera* camera)
    {
        m_activeCamera = camera;
    }

    Camera* World::GetActiveCamera() const
    {
        return m_activeCamera;
    }

    void World::SyncActiveCamera(Application& app) const
    {
        if (m_activeCamera == nullptr)
        {
            return;
        }

        app.GetWindow().SetCamera(*m_activeCamera);
    }

    void World::SetBounds(const sf::FloatRect& bounds)
    {
        m_bounds = bounds;
        m_hasBounds = true;
    }

    const sf::FloatRect& World::GetBounds() const
    {
        return m_bounds;
    }

    bool World::HasBounds() const
    {
        return m_hasBounds;
    }

    void World::ConstrainActorsToBounds() const
    {
        if (!m_hasBounds)
        {
            return;
        }

        for (const auto& actor : m_actors)
        {
            actor->ConstrainToWorldBounds(m_bounds);
        }
    }
}
