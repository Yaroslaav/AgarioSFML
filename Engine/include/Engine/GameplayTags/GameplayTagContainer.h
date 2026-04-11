#pragma once
#include <unordered_set>

#include "GameplayTag.h"

namespace Engine
{
    class GameplayTagContainer
    {
    public:
        void AddTag(const GameplayTag &tag);
        void RemoveTag(const GameplayTag &tag);

        [[nodiscard]] bool HasTagExact(const GameplayTag &tag) const;
        [[nodiscard]] bool HasTag(const GameplayTag &tag) const;

    private:
        std::unordered_set<GameplayTag, GameplayTagHash> m_tags;
    };
}
