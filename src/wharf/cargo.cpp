#include "wharf/cargo.hpp"

wharf::cargo::cargo(const char* name, callback on_ready) : on_ready_f{ on_ready }
{
    cargo_name = name;
    cargo_is_boated = wharf::vessel().cargo_bay().take_ownership_of(*this);
}

auto wharf::cargo::on_ready() -> void {
    if(has_been_readied()) return;

    on_ready_f(*this);
    cargo_has_been_readied = true;
}

// Just returns a dummy implementation in case it's not being
// loaded from a host application.
[[gnu::weak]] auto wharf::vessel() -> wharf::sunken_ship&
{
    static wharf::sunken_ship vessel;
    return vessel;
}
