#include "wharf/wharf.hpp"

auto wharf::sunken_ship::load([[maybe_unused]] std::string_view path)          -> bool { return false; }
auto wharf::sunken_ship::unload([[maybe_unused]] std::string_view libname)     -> bool { return false; }
auto wharf::sunken_ship::take_ownership_of([[maybe_unused]] wharf::cargo& lib) -> bool { return false; }
auto wharf::sunken_ship::ready_unreadied_libs()                                -> void {}

constexpr wharf::sunken_ship::cargo_bay_proxy::cargo_bay_proxy(wharf::sunken_ship& s)
    : ship{ s }
{}

auto wharf::sunken_ship::cargo_bay_proxy::take_ownership_of(wharf::cargo& lib) -> bool
{
    return ship.take_ownership_of(lib);
}

auto wharf::sunken_ship::cargo_bay() -> wharf::sunken_ship::cargo_bay_proxy
{
    return {*this};
}

