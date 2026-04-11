#pragma once

#include <cstddef>
#include <functional>
#include <string>
#include <string_view>
#include <utility>

namespace Engine
{

    class GameplayTag
    {
    public:
        GameplayTag() = default;
        explicit GameplayTag(const std::string_view name) :
            m_name(name)
        {
        }

        [[nodiscard]] std::string_view GetName() const
        {
            return m_name;
        }

        [[nodiscard]] bool IsValid() const
        {
            return !m_name.empty();
        }

        [[nodiscard]] bool MatchesExact(const GameplayTag& other) const
        {
            return m_name == other.m_name;
        }

        [[nodiscard]] bool MatchesTag(const GameplayTag& other) const
        {
            if (m_name == other.m_name)
            {
                return true;
            }

            if (!other.IsValid() || m_name.size() <= other.m_name.size())
            {
                return false;
            }

            return m_name[other.m_name.size()] == '.'
                && m_name.substr(0, other.m_name.size()) == other.m_name;
        }

        [[nodiscard]] bool operator==(const GameplayTag& other) const
        {
            return m_name == other.m_name;
        }

    private:
        std::string m_name;
    };

    struct GameplayTagHash
    {
        std::size_t operator()(const GameplayTag& tag) const noexcept
        {
            return std::hash<std::string_view>{}(tag.GetName());
        }
    };
}
