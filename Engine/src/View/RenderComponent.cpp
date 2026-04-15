#include "Engine/View/RenderComponent.h"

#include "Engine/Core/Application.h"
#include "Engine/View/RenderSystem.h"

namespace Engine
{
    RenderComponent::~RenderComponent()
    {
        EndPlay();
    }

    void RenderComponent::BeginPlay(Application& app)
    {
        if (m_renderHandle.IsValid())
        {
            return;
        }

        m_renderSystem = &app.GetRenderSystem();
        m_renderHandle = m_renderSystem->Register(this);
    }

    void RenderComponent::EndPlay()
    {
        if (!m_renderSystem || !m_renderHandle.IsValid())
        {
            return;
        }

        m_renderSystem->Unregister(m_renderHandle);
        m_renderHandle = {};
        m_renderSystem = nullptr;
    }
}
