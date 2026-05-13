#pragma once
#include "Actor.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <random>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace Engine
{
    class Camera;

    class World
    {
    public:
        virtual ~World() = default;

        template<typename T, typename... TArgs>
        T* SpawnActor(TArgs&&... args)
        {
            static_assert(std::is_base_of_v<Actor, T>, "T must derive from Actor");

            auto actor = std::make_unique<T>(std::forward<TArgs>(args)...);
            T* rawPtr = actor.get();
            rawPtr->SetWorld(this);
            GetOrCreateBucket<T>().actors.push_back(rawPtr);
            m_pendingActors.push_back(std::move(actor));
            return rawPtr;
        }

        template<typename T>
        [[nodiscard]] const std::vector<T*>& GetAllActorsOfClass() const
        {
            static_assert(std::is_base_of_v<Actor, T>, "T must derive from Actor");

            const auto it = m_actorBuckets.find(std::type_index(typeid(T)));
            if (it == m_actorBuckets.end())
            {
                static const std::vector<T*> emptyActors;
                return emptyActors;
            }

            return static_cast<const ActorBucket<T>&>(*it->second).actors;
        }

        virtual void BeginPlay(Application& app);
        virtual void EndPlay();
        virtual void Tick(Application& app, float deltaTime);
        virtual void Render(Application& app) const;

        void SetActiveCamera(Camera* camera);
        [[nodiscard]] Camera* GetActiveCamera() const;
        void SetBounds(const sf::FloatRect& bounds);
        [[nodiscard]] const sf::FloatRect& GetBounds() const;
        [[nodiscard]] sf::Vector2f GetCenter() const;
        [[nodiscard]] bool HasBounds() const;
        [[nodiscard]] sf::Vector2f GetRandomPositionInBounds(float padding = 0.f);


    private:
        struct ActorBucketBase
        {
            virtual ~ActorBucketBase() = default;
        };

        template<typename T>
        struct ActorBucket final : ActorBucketBase
        {
            std::vector<T*> actors;
        };

        template<typename T>
        ActorBucket<T>& GetOrCreateBucket()
        {
            const std::type_index typeIndex(typeid(T));
            const auto it = m_actorBuckets.find(typeIndex);
            if (it != m_actorBuckets.end())
            {
                return static_cast<ActorBucket<T>&>(*it->second);
            }

            auto bucket = std::make_unique<ActorBucket<T>>();
            ActorBucket<T>* bucketPtr = bucket.get();
            m_actorBuckets.emplace(typeIndex, std::move(bucket));
            return *bucketPtr;
        }

        std::vector<std::unique_ptr<Actor>> m_actors;
        std::vector<std::unique_ptr<Actor>> m_pendingActors;
        std::unordered_map<std::type_index, std::unique_ptr<ActorBucketBase>> m_actorBuckets;
        Camera* m_activeCamera = nullptr;
        sf::FloatRect m_bounds{};
        bool m_hasBounds = false;
        std::mt19937 m_randomEngine{std::random_device{}()};

        void FlushPendingActors(Application& app);
        void SyncActiveCamera(Application& app) const;
        void ConstrainActorsToBounds() const;
    };
}
