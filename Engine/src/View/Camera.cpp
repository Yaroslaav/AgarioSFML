#include "Engine/View/Camera.h"

namespace Engine
{
    Camera::Camera(const sf::Vector2f &center, const sf::Vector2f &size) :
        m_view(center, size)
    {
    }

    void Camera::SetCenter(const sf::Vector2f &center)
    {
        m_view.setCenter(center);
    }

    void Camera::Move(const sf::Vector2f &offset)
    {
        m_view.move(offset);
    }

    void Camera::SetSize(const sf::Vector2f &size)
    {
        m_view.setSize(size);
    }

    void Camera::Zoom(const float magnitude)
    {
        m_view.zoom(magnitude);
    }
}
