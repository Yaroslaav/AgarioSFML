#include "Engine/View/Camera.h"

namespace Engine
{
    Camera::Camera(const sf::Vector2f &center, const sf::Vector2f &size) :
        m_view(center, size)
    {
        SetCenter(center);
    }

    void Camera::SetCenter(const sf::Vector2f &center)
    {
        GetTransform().SetPosition(center);
        m_view.setCenter(center);
    }

    void Camera::Move(const sf::Vector2f &offset)
    {
        SetCenter(GetCenter() + offset);
    }

    void Camera::SetSize(const sf::Vector2f &size)
    {
        m_view.setSize(size);
    }

    void Camera::Zoom(const float magnitude)
    {
        m_view.zoom(magnitude);
    }

    void Camera::SetFocusActor(const Actor &target)
    {
        m_focusedTransform = target.GetComponent<TransformComponent>();
    }

    void Camera::ClearFocusActor()
    {
        m_focusedTransform = nullptr;
    }

    bool Camera::IsFocusedOn(const Actor& target) const
    {
        return m_focusedTransform == target.GetComponent<TransformComponent>();
    }

    void Camera::Tick(Application &app, const float deltaTime)
    {
        Actor::Tick(app, deltaTime);

        if (m_focusedTransform != nullptr)
        {
            SetCenter(m_focusedTransform->GetPosition());
            return;
        }

        m_view.setCenter(GetActorPosition());
    }
}
