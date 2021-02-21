#include "wharf/cargo.hpp"

#include "wharf/wharf.hpp"

wharf::cargo::cargo(const char* name)
    : cargo_name{ name }
    , is_boated{ wharf::vessel().cargo_bay().take_ownership_of(*this) }
{}

// Just returns a dummy implementation in case it's not being
// loaded from a host application.
[[gnu::weak]] auto wharf::vessel() -> wharf::sunken_ship&
{
    static wharf::sunken_ship vessel;
    return vessel;
}
