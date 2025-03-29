project('imgui-util-events', 'cpp')

imgui_util_events_dirs = include_directories('include')

imgui_util_events_dep = declare_dependency(
    include_directories: imgui_util_events_dirs,
)

meson.override_dependency('imgui-util-events', imgui_util_events_dep)


# Build examples only when not being used as a subproject
if not meson.is_subproject()
  subdir('examples')
endif
