#pragma once

#include <cstdint>
#include <vector>

#include "Engine/View/RenderHandle.h"

namespace Engine
{
    class RenderComponent;
    class Window;

    class RenderSystem
    {
    public:
        RenderHandle Register(RenderComponent* component);
        void Unregister(RenderHandle handle);
        void DrawAll(Window& window) const;

    private:
        struct RenderEntry
        {
            uint32_t generation = 0;
            RenderComponent* component = nullptr;
            bool occupied = false;
        };

        std::vector<RenderEntry> m_entries;
        std::vector<uint32_t> m_freeList;
    };
}
