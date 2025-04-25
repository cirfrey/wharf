project('wharf', 'cpp',
    version: '0.0.0',
    default_options : [
        'cpp_std=c++17',
    ],
)

incdir = include_directories('src')

wharf_sources = files(
    'src/wharf/wharf.cpp',
)

host_dependencies = [
    meson.get_compiler('cpp').find_library('dl'),
]

host_sources = files(
    'src/wharf/vessels/boat.cpp',
)

cargo_sources = files(
    'src/wharf/cargo.cpp',
)

host_lib = library('wharf_host', include_directories: incdir, dependencies: host_dependencies, sources: wharf_sources + host_sources)
host_dep = declare_dependency(   include_directories: incdir, dependencies: host_dependencies, link_with: host_lib, link_args: '-rdynamic')

cargo_lib = library('wharf_cargo', include_directories: incdir, sources: wharf_sources + cargo_sources)
cargo_dep = declare_dependency(    include_directories: incdir, link_with: cargo_lib)

subdir('tests')
