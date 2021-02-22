#include "wharf/cargo.hpp"

#include <iostream>

auto plugin = wharf::cargo{
    "hello_world",
    []{
        std::cout << "Howdy, world\n";
    },
    [](auto& cargo){
        std::cout << '[' << cargo.cargo_name << "] Goodbye, world\n";
    }
};
