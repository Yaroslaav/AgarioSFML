#pragma once
#include "Actor.h"

namespace Engine
{
    class Camera;

    class World
    {
    public:
        template<typename T, typename... TArgs>
        T* SpawnActor(TArgs&&... args)
        {
            static_assert(std::is_base_of_v<Actor, T>, "T must derive from Actor");

            auto actor = std::make_unique<T>(std::forward<TArgs>(args)...);
            T* rawPtr = actor.get();
            m_pendingActors.push_back(std::move(actor));
            return rawPtr;
        }

        void BeginPlay(Application& app);
        void EndPlay();
        void Tick(Application& app, float deltaTime);
        void Render(Application& app) const;
        void SetActiveCamera(Camera* camera);
        [[nodiscard]] Camera* GetActiveCamera() const;


    private:
        std::vector<std::unique_ptr<Actor>> m_actors;
        std::vector<std::unique_ptr<Actor>> m_pendingActors;
        Camera* m_activeCamera = nullptr;

        void FlushPendingActors();
        void SyncActiveCamera(Application& app) const;
    };
}
