#pragma once
#include <algorithm>
#include <cstdint>
#include <functional>
#include <utility>
#include <vector>

namespace Engine
{

    template<typename... TArgs>
    class Event
    {
    public:
        using Handler = std::function<void(TArgs...)>;
        using EventHandle = uint64_t; //may be smth bigger in the future

        EventHandle AddListener(Handler handler)
        {
            m_handlers.emplace_back(++m_lastID, std::move(handler));
            return m_lastID;
        }

        void RemoveListener(EventHandle evenHandle)
        {
            m_handlers.erase(std::remove_if(m_handlers.begin(), m_handlers.end(),
                [evenHandle](const auto& pair) {
                return pair.first == evenHandle;
            }), m_handlers.end());
        }

        void Broadcast(TArgs... args)
        {
            for (auto& [eventHandle, handler] : m_handlers)
            {
                handler(args...);
            }
        }
        void Clear()
        {
            m_handlers.clear();
        }
    private:
        std::vector<std::pair<EventHandle, Handler>> m_handlers;
        EventHandle m_lastID = 0;
    };
}
