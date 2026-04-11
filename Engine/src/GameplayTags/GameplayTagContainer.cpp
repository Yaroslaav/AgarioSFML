#include "Engine/GameplayTags/GameplayTagContainer.h"

#include <algorithm>

namespace Engine
{
    void GameplayTagContainer::AddTag(const GameplayTag& tag)
    {
        if (!tag.IsValid() || HasTagExact(tag))
        {
            return;
        }

        m_tags.insert(tag);
    }

    void GameplayTagContainer::RemoveTag(const GameplayTag& tag)
    {
        m_tags.erase(tag);
    }

    bool GameplayTagContainer::HasTagExact(const GameplayTag& tag) const
    {
        return m_tags.find(tag) != m_tags.end();
    }

    bool GameplayTagContainer::HasTag(const GameplayTag &tag) const
    {
        if (!tag.IsValid())
        {
            return false;
        }

        if (HasTagExact(tag))
        {
            return true;
        }

        return std::any_of(m_tags.begin(), m_tags.end(), [&tag](const GameplayTag& existing)
        {
            return existing.MatchesTag(tag);
        });
    }
}
