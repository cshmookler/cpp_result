// Standard includes
#include <iostream>

// External includes
#include "../include/result.hpp"

res::result_t func(bool value) {
    if (value) {
        return res::success;
    }

    return RES_NEW_ERROR("Operation failed!");
}

int main() {
    // This operation succeeds.
    auto res = func(true);
    if (res.failure()) {
        std::cout << res.error().string() << '\n';
        // return 1; // NOTE: You'd normally return here.
    }

    // This operation fails.
    res = func(false);
    if (res.failure()) {
        std::cout << res.error().string() << '\n';
        // return 1; // NOTE: You'd normally return here.
    }

    return 0;
}
