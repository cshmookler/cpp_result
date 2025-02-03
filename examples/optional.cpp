// Standard includes
#include <cstddef>
#include <iostream>
#include <vector>

// External includes
#include "../include/optional.hpp"

res::optional_t<size_t> multiply(size_t lhs, size_t rhs) {
    if (lhs == rhs) {
        return RES_NEW_ERROR("lhs and rhs cannot be the same value");
    }

    return lhs * rhs;
}

res::optional_t<std::vector<size_t>> func(size_t count) {
    if (count == 0) {
        return RES_NEW_ERROR("count cannot be zero");
    }

    const size_t limit = 100000;

    std::vector<size_t> values;

    for (size_t _ = 0; _ < count; ++_) {
        auto product = multiply(limit - count, count);
        if (product.has_error()) {
            return RES_TRACE(product.error());
        }

        values.push_back(product.value());
    }

    return values;
}

int main() {
    // This operation succeeds.
    auto res = func(5);
    if (res.has_error()) {
        std::cout << res.error().string() << '\n';
        // return 1; // NOTE: You'd normally return here.
    }

    // This operation fails.
    res = func(0);
    if (res.has_error()) {
        std::cout << res.error().string() << '\n';
        // return 1; // NOTE: You'd normally return here.
    }

    // This operation also fails.
    res = func(50000);
    if (res.has_error()) {
        std::cout << res.error().string() << '\n';
        // return 1; // NOTE: You'd normally return here.
    }

    return 0;
}
