#include "Engine/View/Window.h"

#include "Engine/Core/Application.h"
#include "Engine/GameplayTags/GameTags.h"

namespace Engine
{
    Window::Window(
        const unsigned int width,
        const unsigned int height,
        const std::string& title,
        const unsigned int frameRate,
        const sf::Keyboard::Key fullscreenToggleKey,
        const sf::Keyboard::Key zoomInKey,
        const sf::Keyboard::Key zoomOutKey,
        const float zoomInFactor,
        const float zoomOutFactor,
        const bool startFullscreen) :
        m_frameRate(frameRate),
        m_title(title),
        m_renderWindow(sf::VideoMode({width, height}), title),
        m_defaultCamera(
            sf::Vector2f(static_cast<float>(width) * 0.5f, static_cast<float>(height) * 0.5f),
            sf::Vector2f(width, height)),
        m_fullscreenToggleKey(fullscreenToggleKey),
        m_zoomInKey(zoomInKey),
        m_zoomOutKey(zoomOutKey),
        m_zoomInFactor(zoomInFactor),
        m_zoomOutFactor(zoomOutFactor),
        m_isFullscreen(startFullscreen),
        m_windowedSize(width, height)
    {
        if (m_isFullscreen)
        {
            m_renderWindow.create(sf::VideoMode::getDesktopMode(), m_title, sf::Style::None);
            m_defaultCamera.SetSize(static_cast<sf::Vector2f>(m_renderWindow.getSize()));
        }

        m_renderWindow.setView(m_defaultCamera.GetView());
        m_renderWindow.setFramerateLimit(m_frameRate);
    }

    void Window::Init(Application &app)
    {
        BindKey& screenModeToggleBind = app.GetInput().AddNewBind(m_fullscreenToggleKey, Tags::Engine::Input_ScreenMode_Toggle);
        screenModeToggleBind.OnPressedOnce.AddListener([this]() { ToggleFullScreen(); });

        BindKey& zoomInBind = app.GetInput().AddNewBind(m_zoomInKey, Tags::Engine::Input_Camera_ZoomIn);
        zoomInBind.OnPressedOnce.AddListener([this]() { GetCurrentCamera().Zoom(m_zoomInFactor); });

        BindKey& zoomOutBind = app.GetInput().AddNewBind(m_zoomOutKey, Tags::Engine::Input_Camera_ZoomOut);
        zoomOutBind.OnPressedOnce.AddListener([this]() { GetCurrentCamera().Zoom(m_zoomOutFactor); });
    }

    bool Window::IsOpen() const
    {
        return m_renderWindow.isOpen();
    }

    void Window::Close()
    {
        m_renderWindow.close();
    }

    std::optional<sf::Event> Window::PollEvent()
    {
        return m_renderWindow.pollEvent();
    }

    void Window::Clear(const sf::Color &color)
    {
        m_renderWindow.clear(color);
    }

    void Window::Display()
    {
        m_renderWindow.display();
    }

    sf::Vector2u Window::GetSize() const
    {
        return m_renderWindow.getSize();
    }

    void Window::SetFrameRateLimit(const unsigned int limit)
    {
        m_renderWindow.setFramerateLimit(limit);
    }

    sf::Vector2f Window::MapPixelToCoords(const sf::Vector2i position) const
    {
        return m_renderWindow.mapPixelToCoords(position);
    }

    sf::Vector2i Window::GetMousePixelPosition() const
    {
        return sf::Mouse::getPosition(m_renderWindow);
    }

    void Window::Recreate(const sf::VideoMode &mode, const uint32_t style)
    {
        m_renderWindow.create(mode, m_title, style);
        m_renderWindow.setFramerateLimit(m_frameRate);

        GetCurrentCamera().SetSize(static_cast<sf::Vector2f>(GetSize()));
        m_renderWindow.setView(GetCurrentCamera().GetView());
    }

    void Window::SetWindowed()
    {
        if (!m_isFullscreen)
            return;

        m_isFullscreen = false;
        Recreate(sf::VideoMode(m_windowedSize), sf::Style::Default);
    }

    void Window::SetFullScreen()
    {
        if (m_isFullscreen)
            return;

        m_windowedSize = m_renderWindow.getSize();
        m_isFullscreen = true;
        Recreate(sf::VideoMode::getDesktopMode(), sf::Style::None);
    }

    void Window::ToggleFullScreen()
    {
        if (m_isFullscreen)
            SetWindowed();
        else
            SetFullScreen();
    }

    void Window::SetCamera(Camera& camera)
    {
        m_activeCamera = &camera;
        m_renderWindow.setView(m_activeCamera->GetView());
    }

    Camera & Window::GetCurrentCamera()
    {
        return m_activeCamera ? *m_activeCamera : m_defaultCamera;
    }

    const Camera & Window::GetCurrentCamera() const
    {
        return m_activeCamera ? *m_activeCamera : m_defaultCamera;
    }

    sf::Vector2f Window::GetMouseWorldPosition() const
    {
        return MapPixelToCoords(GetMousePixelPosition());
    }

}
