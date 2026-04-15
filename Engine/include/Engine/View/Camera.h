#pragma once
#include "Engine/World/Actor.h"
#include "SFML/Graphics/View.hpp"
#include "SFML/System/Vector2.hpp"

namespace Engine
{
    class Camera : public Actor
    {
    public:
        Camera() = default;
        Camera(const sf::Vector2f& center, const sf::Vector2f& size);

        void SetCenter(const sf::Vector2f& center);
        void Move(const sf::Vector2f& offset);

        void SetSize(const sf::Vector2f& size);
        void Zoom(float magnitude);

        void SetFocusActor(const Actor& target);
        void ClearFocusActor();

        sf::Vector2f GetCenter() const
        {
            return GetTransform().GetPosition();
        }
        sf::Vector2f GetSize() const
        {
            return m_view.getSize();
        }

        [[nodiscard]] sf::View& GetView()
        {
            return m_view;
        }
        [[nodiscard]] const sf::View& GetView() const
        {
            return m_view;
        }

        void Tick(Application& app, float deltaTime) override;

    private:
        sf::View m_view;
        const TransformComponent* m_focusedTransform = nullptr;
    };
}
