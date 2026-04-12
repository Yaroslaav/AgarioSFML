#pragma once
#include "SFML/Graphics/View.hpp"
#include "SFML/System/Vector2.hpp"

namespace Engine
{
    class Camera
    {
    public:
        Camera() = default;
        Camera(const sf::Vector2f& center, const sf::Vector2f& size);

        void SetCenter(const sf::Vector2f& center);
        void Move(const sf::Vector2f& offset);

        void SetSize(const sf::Vector2f& size);
        void Zoom(float magnitude);

        sf::Vector2f GetCenter() const
        {
            return m_view.getCenter();
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

    private:
        sf::View m_view;
    };
}
