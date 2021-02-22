#include "wharf/wharf.hpp"

auto wharf::sunken_ship::load(std::string_view path)          -> bool { return false; }
auto wharf::sunken_ship::unload(std::string_view libname)     -> bool { return false; }
auto wharf::sunken_ship::take_ownership_of(wharf::cargo& lib) -> bool { return false; }

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

