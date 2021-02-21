#include "wharf/vessels/boat.hpp"

#include <dlfcn.h> // For dlopen and friends
#include <link.h>  // For struct Dl_info and struct link_map.

auto wharf::boat::load(std::string_view path) -> bool
{
    auto handle = dlopen(path.data(), RTLD_NOW | RTLD_LOCAL);
    if (handle) { dlclose(handle); }

    return handle != nullptr;
}

auto wharf::boat::take_ownership_of(wharf::cargo& lib) -> bool
{
    // We need to figure out the handle given a pointer to inside
    // of the dynamically loaded library.
    // Luckly for us, in glibc the handle is the actual linkmap.
    /// TODO: what about other libc implemetations ?
    Dl_info info;
    link_map* handle;
    dladdr1(
        &lib,
        &info,
        reinterpret_cast<void**>(&handle),
        RTLD_DL_LINKMAP);

    /// TODO: maybe check if cargo is already loaded ?

    // Increase the refcount since we are now owners of this aswell.
    dlopen(handle->l_name, RTLD_NOW | RTLD_NOLOAD);

    libs.emplace_back( handle, [](auto h){ dlclose(h); } );
    return true;
}
