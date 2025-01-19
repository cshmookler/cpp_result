// Standard includes
#include <iostream>

// External includes
#include "../cpp_result/error.hpp"

int main() {
    // The creation point of an error must be annotated with a message.
    auto error =
      RES_NEW_ERROR("This is an example error.  The stack trace begins here.");

    error = RES_TRACE(error); // Annotating traces is optional.

    error = RES_ERROR(error, "Traces can be annotated like this.");

    std::cout << error.string() << '\n';
}
