#pragma once
#include "Actor.h"
#include <SFML/Graphics/Rect.hpp>

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
        void SetBounds(const sf::FloatRect& bounds);
        [[nodiscard]] const sf::FloatRect& GetBounds() const;
        [[nodiscard]] bool HasBounds() const;


    private:
        std::vector<std::unique_ptr<Actor>> m_actors;
        std::vector<std::unique_ptr<Actor>> m_pendingActors;
        Camera* m_activeCamera = nullptr;
        sf::FloatRect m_bounds{};
        bool m_hasBounds = false;

        void FlushPendingActors();
        void SyncActiveCamera(Application& app) const;
        void ConstrainActorsToBounds() const;
    };
}
