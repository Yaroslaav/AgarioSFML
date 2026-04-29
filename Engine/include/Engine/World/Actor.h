#pragma once
#include "Engine/Components/ActorComponent.h"
#include "Engine/Components/TransformComponent.h"

#include <SFML/Graphics/Rect.hpp>
#include <memory>
#include <typeindex>
#include <type_traits>
#include <utility>
#include <vector>

namespace Engine
{

    class Application;
    class World;

    class Actor
    {
    public:
        Actor();
        virtual ~Actor() = default;

        virtual void BeginPlay(Application& app);
        virtual void EndPlay();

        virtual void Tick(Application& app, float deltaTime);
        virtual void Render(Application& app);
        virtual void ConstrainToWorldBounds(const sf::FloatRect& bounds);
        [[nodiscard]] virtual float GetRenderSortKey() const;

        [[nodiscard]] bool IsActive() const
        {
            return m_isActive;
        }
        void SetActive(const bool active)
        {
            m_isActive = active;
        }

        template<typename T, typename ... TArgs>
        T* AddComponent(TArgs &&...args)
        {
            static_assert(std::is_base_of_v<ActorComponent, T>, "T must derive from ActorComponent");
            static_assert(!std::is_same_v<TransformComponent, T>, "Actor already owns a TransformComponent");

            auto component = std::make_unique<T>(std::forward<TArgs>(args)...);
            T* rawPtr = component.get();
            rawPtr->SetOwner(this);
            m_components.push_back(std::move(component));
            return rawPtr;
        }

        template<typename T>
        T* GetComponent() const
        {
            static_assert(std::is_base_of_v<ActorComponent, T>, "T must derive from ActorComponent");

            if constexpr (std::is_same_v<TransformComponent, T>)
            {
                return const_cast<T*>(&m_transformComponent);
            }

            for (const auto& component : m_components)
            {
                if (component->IsA<T>())
                {
                    return static_cast<T*>(component.get());
                }
            }

            for (const auto& component : m_components)
            {
                if (auto* ptr = dynamic_cast<T*>(component.get()))
                {
                    return ptr;
                }
            }
            return nullptr;
        }

        template<typename T>
        [[nodiscard]] bool IsA() const
        {
            return std::type_index(typeid(*this)) == std::type_index(typeid(T));
        }

        [[nodiscard]] const sf::Vector2f& GetActorPosition() const
        {
            return GetTransform().GetPosition();
        }

        [[nodiscard]] TransformComponent& GetTransform()
        {
            return m_transformComponent;
        }

        [[nodiscard]] const TransformComponent& GetTransform() const
        {
            return m_transformComponent;
        }

        [[nodiscard]] World* GetWorld() const
        {
            return m_world;
        }

        template<typename T>
        [[nodiscard]] T* GetWorld() const
        {
            return dynamic_cast<T*>(m_world);
        }
    private:
        friend class World;

        void SetWorld(World* world)
        {
            m_world = world;
        }

        bool m_isActive = true;
        World* m_world = nullptr;
        TransformComponent m_transformComponent;
        std::vector<std::unique_ptr<ActorComponent>> m_components;
    };

}
