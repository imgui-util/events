#pragma once
#include <string>
#include <optional>

template <typename T>
struct NavigationEvent
{
    std::string routeName;
    std::optional<T> data;
};

template <>
struct NavigationEvent<void>
{
    std::string routeName;
};
