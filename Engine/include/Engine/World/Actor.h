#pragma once
#include "Engine/Components/ActorComponent.h"
#include "Engine/Components/TransformComponent.h"

#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

namespace Engine
{

    class Application;

    class Actor
    {
    public:
        Actor();
        virtual ~Actor() = default;

        virtual void BeginPlay(Application& app);
        virtual void EndPlay();

        virtual void Tick(Application& app, float deltaTime);
        virtual void Render(Application& app);

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
                if (auto* ptr = dynamic_cast<T*>(component.get()))
                {
                    return ptr;
                }
            }
            return nullptr;
        }

        [[nodiscard]] TransformComponent& GetTransform()
        {
            return m_transformComponent;
        }

        [[nodiscard]] const TransformComponent& GetTransform() const
        {
            return m_transformComponent;
        }
    private:
        bool m_isActive = true;
        TransformComponent m_transformComponent;
        std::vector<std::unique_ptr<ActorComponent>> m_components;
    };

}
