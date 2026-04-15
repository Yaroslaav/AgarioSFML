#pragma once

#include <cstdint>
#include <limits>

namespace Engine
{
    struct RenderHandle
    {
        uint32_t index = std::numeric_limits<uint32_t>::max();
        uint32_t generation = 0;

        [[nodiscard]] bool IsValid() const
        {
            return index != std::numeric_limits<uint32_t>::max();
        }
    };
}
