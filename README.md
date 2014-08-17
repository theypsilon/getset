getset
======

```cpp
#include "getset.hpp"
#include <iostream>

using namespace accessor;

struct Data {
    getset<std::string> a;
    getset<std::string> b;
    getset<std::string> c;
};

int main() {
    Data x{"Hello","I'm not a blank space","World."};
    x.b(" ");
    std::cout << x.a() << x.b() << x.c() << std::endl;
    return 0;
}

/* output: "Hello World." */
```

Just add this simple template to your types and you will have a getter & setter interface that eventually you will be able to modify in the future without any modification in client code. 

This has **zero** overhead. You may compare the asm this code generates, with the one you get when you replace the getset statements with raw variable declarations and simple assignments.
