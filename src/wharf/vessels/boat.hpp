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

        boat() = default;
        virtual ~boat() = default;

        virtual auto load(std::string_view path) -> bool override;

    protected:
        virtual auto take_ownership_of(wharf::cargo& lib) -> bool override;

        std::vector<lib_handle> libs;
    };
}
