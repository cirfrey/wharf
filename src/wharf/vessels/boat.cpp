#include "wharf/vessels/boat.hpp"

#include "wharf/cargo.hpp"

#include <dlfcn.h> // For dlopen and friends.
#include <link.h>  // For struct Dl_info and struct link_map.

auto wharf::boat::load(std::string_view path) -> bool
{
    unload(path);

    auto handle = dlopen(path.data(), RTLD_NOW | RTLD_LOCAL);
    if (handle) { dlclose(handle); }

    return handle != nullptr;
}

auto wharf::boat::unload(std::string_view path) -> bool
{
    auto it = libs.find(path.data());
    if(it == libs.end()) { return false; }

    libs.erase(it);
    return true;
}

auto wharf::boat::take_ownership_of(wharf::cargo& cargo) -> bool
{
    // We need to figure out the handle given a pointer to inside
    // of the dynamically loaded library, for that we are going to
    // use dladdr1() using that pointer to get the link map, and then
    // dlopen() the object again to get the handle.

    auto dummy_info = Dl_info{};
    link_map* link_map = nullptr;
    dladdr1(
        &cargo,
        &dummy_info,
        reinterpret_cast<void**>(&link_map),
        RTLD_DL_LINKMAP);

    // dlopen() also increases the object's refcount (when it reaches 0
    // the shared object is deallocated), which is what we want since we want
    // to own it aswell.
    auto handle = dlopen(link_map->l_name, RTLD_NOW | RTLD_NOLOAD);
    /// TODO: What if handle == nullptr ?

    // We create the lib before trying to insert to make sure it's cleaned
    // up properly if there already exists a lib with the same name.
    auto lib = boat::lib{cargo, handle};

    if( libs.count(link_map->l_name) ) { return false; }

    libs.emplace( link_map->l_name, std::move(lib) );
    return true;
}

wharf::boat::lib::lib(wharf::cargo& c, void* h)
    : cargo{ &c }
    , handle{ h, &dlclose }
{}
