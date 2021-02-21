#include "wharf/host.hpp"

int main() {
    wharf::vessel().load("tests/plugin_hello_world/libplugin_hello_world.so");

    return 0;
}
