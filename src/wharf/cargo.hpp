#pragma once

#include "wharf/wharf.hpp"

#include <type_traits> // For std::is_invocable.
#include <functional> // For std::function.

namespace wharf
{
    class cargo
    {
    public:
        template <
            typename Func1 = std::function<void(void)>,
            typename Func2 = std::function<void(void)>
        >
        cargo(const char* name, Func1&& on_init = []{}, Func2&& on_deinit = []{});
        virtual ~cargo();

        const char* const cargo_name;
        const bool is_boated;

    private:
        std::function<void(void)> on_destruction;
    };
}

template< typename Func1, typename Func2 >
wharf::cargo::cargo(const char* name, Func1&& on_init, Func2&& on_deinit)
    : cargo_name{ name }
    , is_boated{ wharf::vessel().cargo_bay().take_ownership_of(*this) }
    , on_destruction{
        [on_deinit = std::forward<Func2>(on_deinit), this]{
            if constexpr( std::is_invocable_v<Func2, wharf::cargo&>) {
                on_deinit(*this);
            } else {
                on_deinit();
            }
        }
    }
{
    /// TODO: Defer this call to when the function returns somehow, just
    // in case someone tries to wharf::vessel().unload(cargo.cargo_name)
    // or something equally weird inside on_init().
    if(is_boated)
    {
        if constexpr( std::is_invocable_v<Func1, wharf::cargo&> ) {
            on_init(*this);
        } else {
            on_init();
        }
    }
}