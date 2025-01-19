// External includes
#include <gtest/gtest.h>

// Local includes
#include "../cpp_result/result.hpp"

TEST(result_test, result_default_constructor) {
    res::result_t result;

    ASSERT_TRUE(result.success());
    ASSERT_FALSE(result.failure());
    ASSERT_GT(result.error().string().size(), 0);
}

TEST(result_test, result_copy_error_constructor) {
    res::error_t error{ "some error" };
    res::result_t result{ error };

    ASSERT_FALSE(result.success());
    ASSERT_TRUE(result.failure());
    ASSERT_STREQ(result.error().string().c_str(), error.string().c_str());
}

TEST(result_test, result_move_error_constructor) {
    res::error_t error{ "" };
    res::result_t result{ std::move(error) };

    ASSERT_FALSE(result.success());
    ASSERT_TRUE(result.failure());
    ASSERT_EQ(result.error().string().size(), 0);
}

TEST(result_test, result_copy_result_constructor_success) {
    res::result_t result_1;
    ASSERT_TRUE(result_1.success());
    ASSERT_FALSE(result_1.failure());

    res::result_t result_2{ result_1 };
    ASSERT_TRUE(result_2.success());
    ASSERT_FALSE(result_2.failure());

    ASSERT_STREQ(
      result_1.error().string().c_str(), result_2.error().string().c_str());
}

TEST(result_test, result_copy_result_constructor_failure) {
    res::result_t result_1{ res::error_t{ "some error" } };
    ASSERT_FALSE(result_1.success());
    ASSERT_TRUE(result_1.failure());

    res::result_t result_2{ result_1 };
    ASSERT_FALSE(result_2.success());
    ASSERT_TRUE(result_2.failure());

    ASSERT_STREQ(
      result_1.error().string().c_str(), result_2.error().string().c_str());
}

TEST(result_test, result_move_result_constructor_success) {
    res::result_t result_1{};
    res::result_t result_2{ std::move(result_1) };
    ASSERT_TRUE(result_2.success());
    ASSERT_FALSE(result_2.failure());

    ASSERT_GT(result_2.error().string().size(), 0);
}

TEST(result_test, result_move_result_constructor_failure) {
    res::result_t result_1{ res::error_t{ "" } };
    res::result_t result_2{ std::move(result_1) };
    ASSERT_FALSE(result_2.success());
    ASSERT_TRUE(result_2.failure());

    ASSERT_EQ(result_2.error().string().size(), 0);
}

TEST(result_test, result_copy_equal_operator_success) {
    res::result_t result_1{};
    res::result_t result_2 = result_1;
    ASSERT_TRUE(result_2.success());
    ASSERT_FALSE(result_2.failure());

    ASSERT_STREQ(
      result_1.error().string().c_str(), result_2.error().string().c_str());
}

TEST(result_test, result_copy_equal_operator_failure) {
    res::result_t result_1{ res::error_t{ "some error" } };
    res::result_t result_2 = result_1;
    ASSERT_FALSE(result_2.success());
    ASSERT_TRUE(result_2.failure());

    ASSERT_STREQ(
      result_1.error().string().c_str(), result_2.error().string().c_str());
}

TEST(result_test, result_move_equal_operator_success) {
    res::result_t result_1{};
    res::result_t result_2 = std::move(result_1);
    ASSERT_TRUE(result_2.success());
    ASSERT_FALSE(result_2.failure());

    ASSERT_GT(result_2.error().string().size(), 0);
}

TEST(result_test, result_move_equal_operator_failure) {
    res::result_t result_1{ res::error_t{ "" } };
    res::result_t result_2 = std::move(result_1);
    ASSERT_FALSE(result_2.success());
    ASSERT_TRUE(result_2.failure());

    ASSERT_EQ(result_2.error().string().size(), 0);
}

TEST(result_test, result_success) {
    res::result_t result = res::success;
    ASSERT_TRUE(result.success());
    ASSERT_FALSE(result.failure());

    ASSERT_GT(result.error().string().size(), 0);
}
