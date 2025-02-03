// Standard includes
#include <iostream>

// External includes
#include "../include/error.hpp"

int main() {
    // The creation point of an error must be annotated with a message.
    auto error =
      RES_NEW_ERROR("This is an example error.  The stack trace begins here.");

    // Annotating traces is optional.
    error = RES_TRACE(error);

    // This trace is annotated with message. New message are appended to the
    // existing message.
    error = RES_ERROR(error, "Traces can be annotated like this.");

    // New errors are completely independent from other errors.
    auto other_error = RES_NEW_ERROR("This is another error.");

    // Errors can be concatonated with other errors.
    error = RES_CONCAT(error, other_error);

    std::cout << error.string() << '\n';
}
