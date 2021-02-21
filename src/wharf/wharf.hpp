// The common interface between the vessel (host) and cargo (plugins).
#pragma once

#include <string_view>

namespace wharf
{
    /*
     * A dummy implementation of the interface.
     * When there is no host this class is used, see wharf::vessel().
     */
    class sunken_ship
    {
    public:
        /*
         * This should just load and then unload the dynamic library,
         * it is up to the library to make sure it stays alive after being
         * unloaded, mainly by calling take_ownership_of(this) (done by wharf::cargo::cargo()).
         */
        virtual auto load(std::string_view path) -> bool;

        /*
         * Uses a pointer from inside a dynamically loaded library to
         * figure out it's handle and increase it's refcount (by dlopen()'ing it again).
         * This is used to make sure the cargo isn't destroyed after being load()'ed.
         */
        virtual auto take_owership_of(void* lib) -> bool;

        sunken_ship() = default;
        virtual ~sunken_ship() = default;
    };

    /*
     * For cargo, this will be a weak function returning the dummy implementation.
     * This way, when the library is loaded from a host application this function
     * will be overriden to return the host's implemetation.
     */
    auto vessel() -> wharf::sunken_ship&;
}
