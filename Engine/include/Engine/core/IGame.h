#pragma once

namespace Engine
{
    class Application;

    class IGame
    {
    public:
        virtual ~IGame() = default;

        virtual void OnInit(Application& app) = 0;
        virtual void OnEvent(Application& app) = 0;
        virtual void OnUpdate(Application& app, float deltaTime) = 0;
        virtual void OnRender(Application& app) = 0;
        virtual void OnShutdown(Application& app) = 0;
    };
}