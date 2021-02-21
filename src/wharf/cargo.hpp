#pragma once

#include "wharf/wharf.hpp"

#include <type_traits> // for std::is_invocable.

namespace wharf
{
    class cargo
    {
    public:
        cargo(const char* name);

        template <typename Func>
        cargo(const char* name, Func on_init);

        virtual ~cargo() = default;

        const char* const cargo_name;
        const bool is_boated;
    };
}

template <typename Func>
wharf::cargo::cargo(const char* name, Func on_init) : cargo(name)
{
    if constexpr(std::is_invocable<Func, wharf::cargo&>::value) {
        if(is_boated) {on_init(this);}
    } else {
        if(is_boated) {on_init();}
    }
}