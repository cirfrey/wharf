test(
    'plugin_hello_world',
    executable('plugin_hello_world', 'src/main.cpp', link_args: '-rdynamic', dependencies: host_dep),
)

declare_dependency(
    link_with: shared_library('plugin_hello_world', 'src/plugin.cpp', dependencies: cargo_dep)
)
