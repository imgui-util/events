#pragma once
#include <functional>
#include <vector>
#include <algorithm>
#include <cstddef>

template <typename Event>
class EventDispatcher
{
public:
    using Listener = std::function<void(const Event &)>;
    using ListenerID = size_t;

    ListenerID addListener(Listener listener)
    {
        size_t id = nextId++;
        listeners.emplace_back(id, std::move(listener));
        return id;
    }

    void removeListener(ListenerID id)
    {
        listeners.erase(std::remove_if(listeners.begin(),
                                       listeners.end(),
                                       [id](const auto &p)
                                       {
                                           return p.first == id;
                                       }),
                        listeners.end());
    }

    void dispatch(const Event &event)
    {
        for (const auto &[id, listener] : listeners)
        {
            if (listener)
                listener(event);
        }
    }

private:
    std::vector<std::pair<ListenerID, Listener>> listeners;
    size_t nextId = 0;
};
