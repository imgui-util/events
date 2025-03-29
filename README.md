# ImGui Util Events

This is a simple library for dispatching events in ImGui.

## Usage

```cpp
#include "imgui_util_events.hpp"


EventDispatcher<InputEvent> dispatcher;

dispatcher.addListener([](const InputEvent &event) {
    if (event.type == InputEventType::KeyDown) {
        std::cout << "Key down: " << event.key << std::endl;
    }
});

dispatcher.dispatch(InputEvent(InputEventType::KeyDown, "A")); 

```

