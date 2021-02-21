#pragma once

#include "wharf/wharf.hpp"

#include <vector>
#include <memory>  // For smart_ptrs.

namespace wharf {
    // Generic plugin manager, yours should inherit this.
    class boat : public sunken_ship
    {
    public:
        using lib_handle = std::unique_ptr<void, void(*)(void*)>;

        auto load(std::string_view path) -> bool override;
        auto take_owership_of(void* lib) -> bool override;

        virtual ~boat() = default;

        std::vector<lib_handle> libs;
    };
}
