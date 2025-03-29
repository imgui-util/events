#pragma once
#include <variant>
#include "sdl_key_event.hpp"
#include "glfw_key_event.hpp"

using InputEvent = std::variant<SDLKeyEvent, GLFWKeyEvent>;
