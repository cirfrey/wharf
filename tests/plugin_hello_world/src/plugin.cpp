#include "wharf/cargo.hpp"

#include <iostream>

auto plugin = wharf::cargo{"hello_world", [](){
    std::cout << "Howdy, world\n";
}};
