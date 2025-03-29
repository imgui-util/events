project('imgui-util-events-examples', 'cpp')

imgui_util_events_dep = subproject('imgui-util-events').get_variable('imgui_util_events_dep')
imgui_dep = subproject('imgui').get_variable('imgui_dep')

executable('sdl_example', 'main.cpp', dependencies: [
    imgui_util_events_dep,
    dependency('sdl2', required: true),
    dependency('gl', required: true),
    imgui_dep
])