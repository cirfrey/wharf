#pragma once

#include "wharf/wharf.hpp"

#include <memory> // For smart_ptrs.
#include <string>
#include <map>

namespace wharf {
    // Generic plugin manager, yours should probably be based off of this.
    class boat : public sunken_ship
    {
    public:
        struct lib;

        boat() = default;
        virtual ~boat() = default;

        virtual auto load(std::string_view path) -> bool override;
        virtual auto unload(std::string_view libname) -> bool override;

    protected:
        virtual auto take_ownership_of(wharf::cargo& lib) -> bool override;

        std::map<std::string, lib> libs;
    };

    struct boat::lib {
        using handle_t = std::unique_ptr<void, int (*)(void*)>;

        lib(wharf::cargo& cargo, void* handle);
        lib(lib&&)                    = default;
        auto operator=(lib&&) -> lib& = default;
        virtual ~lib() noexcept       = default;

        // Make it move-only.
        lib(const lib&)                    = delete;
        auto operator=(const lib&) -> lib& = delete;

        wharf::cargo* cargo;

    private:
        handle_t handle;
    };
}
