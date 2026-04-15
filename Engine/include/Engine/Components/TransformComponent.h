#pragma once

#include "Engine/Components/ActorComponent.h"

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Angle.hpp>
#include <SFML/System/Vector2.hpp>

namespace Engine
{
    class TransformComponent : public ActorComponent
    {
    public:
        [[nodiscard]] const sf::Vector2f& GetPosition() const
        {
            return m_position;
        }

        void SetPosition(const sf::Vector2f& position)
        {
            m_position = position;
        }

        void Move(const sf::Vector2f& offset)
        {
            m_position += offset;
        }

        [[nodiscard]] sf::Angle GetRotation() const
        {
            return m_rotation;
        }

        void SetRotation(const sf::Angle rotation)
        {
            m_rotation = rotation.wrapUnsigned();
        }

        void Rotate(const sf::Angle delta)
        {
            SetRotation(m_rotation + delta);
        }

        [[nodiscard]] const sf::Vector2f& GetScale() const
        {
            return m_scale;
        }

        void SetScale(const sf::Vector2f& scale)
        {
            m_scale = scale;
        }

        void ScaleBy(const sf::Vector2f& factor)
        {
            m_scale = {m_scale.x * factor.x, m_scale.y * factor.y};
        }

        template<typename TTransformable>
        void ApplyTo(TTransformable& transformable) const
        {
            transformable.setPosition(m_position);
            transformable.setRotation(m_rotation);
            transformable.setScale(m_scale);
        }

    private:
        sf::Vector2f m_position{};
        sf::Angle m_rotation = sf::Angle::Zero;
        sf::Vector2f m_scale{1.f, 1.f};
    };
}
