#pragma once

#include <string>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace Engine
{
    struct WindowSettings
    {
        unsigned int width = 1280;
        unsigned int height = 720;
        bool startFullscreen = false;
        std::string title = "Application";
    };

    struct RenderSettings
    {
        unsigned int frameRateLimit = 144;
        sf::Color clearColor = sf::Color::Black;
    };

    struct InputSettings
    {
        sf::Keyboard::Key fullscreenToggleKey = sf::Keyboard::Key::F11;
        sf::Keyboard::Key debugToggleKey = sf::Keyboard::Key::F1;
        sf::Keyboard::Key zoomInKey = sf::Keyboard::Key::Equal;
        sf::Keyboard::Key zoomOutKey = sf::Keyboard::Key::Hyphen;
        float zoomInFactor = 0.9f;
        float zoomOutFactor = 1.1f;
    };

    struct DebugSettings
    {
        bool startDebugMode = false;
    };

    struct AppSettings
    {
        WindowSettings window;
        RenderSettings render;
        InputSettings input;
        DebugSettings debug;
    };
}
