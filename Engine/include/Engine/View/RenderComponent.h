#pragma once

#include "Engine/Components/ActorComponent.h"
#include "Engine/View/RenderHandle.h"

namespace Engine
{
    class Application;
    class RenderSystem;
    class Window;

    class RenderComponent : public ActorComponent
    {
    public:
        ~RenderComponent() override;

        void BeginPlay(Application& app) override;
        void EndPlay() override;

        virtual void Draw(Window& window) const = 0;

    private:
        RenderHandle m_renderHandle{};
        RenderSystem* m_renderSystem = nullptr;
    };
}
