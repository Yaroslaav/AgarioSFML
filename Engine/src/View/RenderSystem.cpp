#include "Engine/View/RenderSystem.h"

#include "Engine/View/RenderComponent.h"
#include "Engine/World/Actor.h"
#include "Engine/View/Window.h"

namespace Engine
{
    RenderHandle RenderSystem::Register(RenderComponent* component)
    {
        if (component == nullptr)
        {
            return {};
        }

        if (!m_freeList.empty())
        {
            const uint32_t index = m_freeList.back();
            m_freeList.pop_back();

            RenderEntry& entry = m_entries[index];
            entry.component = component;
            entry.occupied = true;
            return {index, entry.generation};
        }

        m_entries.push_back({0, component, true});
        return {static_cast<uint32_t>(m_entries.size() - 1), 0};
    }

    void RenderSystem::Unregister(const RenderHandle handle)
    {
        if (!handle.IsValid() || handle.index >= m_entries.size())
        {
            return;
        }

        RenderEntry& entry = m_entries[handle.index];
        if (!entry.occupied || entry.generation != handle.generation)
        {
            return;
        }

        entry.component = nullptr;
        entry.occupied = false;
        entry.generation++;
        m_freeList.push_back(handle.index);
    }

    void RenderSystem::DrawAll(Window& window) const
    {
        for (const RenderEntry& entry : m_entries)
        {
            if (!entry.occupied || entry.component == nullptr)
            {
                continue;
            }

            if (const Actor* owner = entry.component->GetOwner(); owner != nullptr && !owner->IsActive())
            {
                continue;
            }

            entry.component->Draw(window);
        }
    }
}
