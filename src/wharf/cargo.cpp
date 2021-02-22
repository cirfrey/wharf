#include "wharf/cargo.hpp"

wharf::cargo::~cargo() { if(is_boated) { on_destruction(); } }

// Just returns a dummy implementation in case it's not being
// loaded from a host application.
[[gnu::weak]] auto wharf::vessel() -> wharf::sunken_ship&
{
    static wharf::sunken_ship vessel;
    return vessel;
}
