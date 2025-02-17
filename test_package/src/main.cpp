// Standard includes
#include <iostream>
#include <string>

// Package includes
#include <cpp_result/all.hpp>

int main() {
    res::optional_t<std::string> optional = std::string{ "Success!" };
    std::cout << optional.value() << std::endl;
}
