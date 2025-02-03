// External includes
#include <gtest/gtest.h>

// Local includes
#include "../include/error.hpp"

TEST(error_test, res_new_error_macro_with_no_message) {
    ASSERT_GT(RES_NEW_ERROR("").string().size(), 0);
}

TEST(error_test, res_new_error_macro_with_message) {
    ASSERT_GT(RES_NEW_ERROR("this is a test").string().size(), 0);
}

TEST(error_test, res_trace_macro_with_no_message) {
    ASSERT_GT(RES_TRACE(RES_NEW_ERROR("")).string().size(), 0);
}

TEST(error_test, res_trace_macro_with_message) {
    ASSERT_GT(RES_TRACE(RES_NEW_ERROR("this is a test")).string().size(), 0);
}

TEST(error_test, res_error_macro_with_no_message) {
    ASSERT_GT(RES_ERROR(RES_NEW_ERROR(""), "").string().size(), 0);
}

TEST(error_test, res_error_macro_with_message) {
    ASSERT_GT(
      RES_ERROR(RES_NEW_ERROR("first test"), "second test").string().size(), 0);
}

TEST(error_test, res_concat_macro_with_no_message) {
    ASSERT_GT(
      RES_CONCAT(RES_NEW_ERROR(""), RES_NEW_ERROR("")).string().size(), 0);
}

TEST(error_test, res_concat_macro_with_message) {
    ASSERT_GT(
      RES_CONCAT(RES_NEW_ERROR("A"), RES_NEW_ERROR("B")).string().size(), 0);
}

TEST(error_test, error_copy_constructor) {
    std::string message = "This is an error message.";
    res::error_t error{ message };
    ASSERT_STREQ(message.c_str(), error.string().c_str());
}

TEST(error_test, error_move_constructor) {
    std::string message = "This is an error message.";
    res::error_t error{ std::move(message) };
    ASSERT_GT(error.string().size(), 0);
}

TEST(error_test, error_string_const_reference) {
    std::string message = "This is an error message.";
    const res::error_t error{ message };
    ASSERT_STREQ(message.c_str(), error.string().c_str());

    message += "a";
    ASSERT_STRNE(message.c_str(), error.string().c_str());

    std::string error_message = error.string();
    // Modifying a copy of the error message should not modify the original
    // error message.
    error_message += "a";
    ASSERT_STRNE(message.c_str(), error.string().c_str());
}

TEST(error_test, error_string_reference) {
    std::string message = "This is an error message.";
    res::error_t error{ message };
    ASSERT_STREQ(message.c_str(), error.string().c_str());

    message += "a";
    ASSERT_STRNE(message.c_str(), error.string().c_str());

    error.string() += "a";
    ASSERT_STREQ(message.c_str(), error.string().c_str());
}
