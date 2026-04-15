#pragma once
#include <optional>
#include <string>

#include "Camera.h"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"

namespace Engine
{
    class Application;

    class Window
    {
    public:
        Window(unsigned int width, unsigned int height, const std::string &title, unsigned int frameRate);

        void Init(Application &app);
        [[nodiscard]] bool IsOpen() const;
        void Close();

        [[nodiscard]] std::optional<sf::Event> PollEvent();

        void Clear(const sf::Color& color = sf::Color::Black);
        void Display();

        [[nodiscard]] sf::Vector2u GetSize() const;
        void SetFrameRateLimit(unsigned int limit);
        [[nodiscard]] sf::Vector2f MapPixelToCoords(sf::Vector2i position) const;
        [[nodiscard]] sf::Vector2i GetMousePixelPosition() const;

        void Recreate(const sf::VideoMode &mode, uint32_t style);
        void SetWindowed();
        void SetFullScreen();
        void ToggleFullScreen();

        void SetCamera(Camera& camera);
        [[nodiscard]] Camera& GetCurrentCamera();
        [[nodiscard]] const Camera& GetCurrentCamera() const;

        [[nodiscard]] sf::Vector2f GetMouseWorldPosition() const;

        template<typename TDrawable>
        void Draw(const TDrawable& drawable)
        {
            m_renderWindow.draw(drawable);
        }

    private:
        unsigned int m_frameRate;
        std::string m_title;
        sf::RenderWindow m_renderWindow;
        Camera m_defaultCamera;
        Camera* m_activeCamera = nullptr;

        bool m_isFullscreen = false;
        sf::Vector2u m_windowedSize = {1280, 720};
    };
}
