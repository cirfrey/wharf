#pragma once

#include "wharf/wharf.hpp"
#include "wharf/vessels/boat.hpp"

auto wharf::vessel() -> wharf::sunken_ship&
{
    static wharf::boat vessel;
    return vessel;
}
