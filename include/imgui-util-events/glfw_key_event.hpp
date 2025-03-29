#pragma once

struct GLFWKeyEvent
{
    int key;      // GLFW_KEY_A, etc.
    int scancode; // GLFW_SCANCODE_A, etc.
    int action;   // GLFW_PRESS, GLFW_RELEASE
    int mods;     // e.g. shift, alt, etc.
};
