#include "../../error/error.h"
#include <iostream>

int main() {
    errmsg("test");
    std::cout << "next..." << std::endl;
    return 0;
}
