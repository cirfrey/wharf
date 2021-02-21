Each plugin must `#include <wharf/cargo.hpp>` and provide a statically initialized
instance of a `wharf::cargo`, like so:
```cpp
#include "wharf/cargo.hpp"

auto plugin = wharf::cargo{ "my_plugin", [](){
    // Do stuff when sucesfully loaded here
}};

```

or like so:
```cpp
#include "wharf/cargo.hpp"

struct my_plugin : public wharf::cargo
{
    my_plugin() : wharf::cargo{ "my_plugin" }
    {
        if(is_boated)
        {
            // Do stuff when sucesfully loaded here
        }
    }
};

auto plugin = my_plugin{};
```

The host application just needs to `#include <wharf/host.hpp>` or provide its own
`wharf::vessel()` implementation. Refer to `wharf/host.hpp`, it's quite simple.

*NOTE: The host application needs to be compiled with `-rdynamic`.*
