#pragma once

#include "wharf/wharf.hpp"

#include <type_traits> // For std::is_invocable.
#include <functional> // For std::function.

namespace wharf
{
    class cargo
    {
    public:
        using callback = void(*)(cargo&);

        cargo(const char* name, callback on_ready = [](auto){});
        virtual ~cargo() = default;

        auto name() const -> const char* { return cargo_name; }
        auto is_boated() const -> bool { return cargo_is_boated; }
        auto has_been_readied() const -> bool { return cargo_has_been_readied; }

        // The vessel calls this some indeterminate amount of
        // time after the library is loaded/created, this means
        // it can actually do work now.
        virtual auto on_ready() -> void;

    private:
        callback on_ready_f;

        const char* cargo_name;
        bool cargo_is_boated;
        bool cargo_has_been_readied = false;
    };
}
