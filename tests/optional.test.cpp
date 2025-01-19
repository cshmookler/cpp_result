// External includes
#include <gtest/gtest.h>

// Local includes
#include "../cpp_result/optional.hpp"

TEST(optional_test, optional_copy_error_constructor) {
    res::error_t error{ "some error" };
    res::optional_t<std::string> optional{ error };
    ASSERT_FALSE(optional.has_value());
    ASSERT_TRUE(optional.has_error());
    ASSERT_THROW(optional.value(), res::bad_optional_access_t);
    ASSERT_STREQ(optional.error().string().c_str(), error.string().c_str());
}

TEST(optional_test, optional_move_error_constructor) {
    res::error_t error{ "" };
    res::optional_t<std::string> optional{ std::move(error) };
    ASSERT_FALSE(optional.has_value());
    ASSERT_TRUE(optional.has_error());
    ASSERT_THROW(optional.value(), res::bad_optional_access_t);
    ASSERT_EQ(optional.error().string().size(), 0);
}

TEST(optional_test, optional_copy_equal_operator_error) {
    res::error_t error{ "some error" };
    res::optional_t<std::string> optional = error;
    ASSERT_FALSE(optional.has_value());
    ASSERT_TRUE(optional.has_error());
    ASSERT_THROW(optional.value(), res::bad_optional_access_t);
    ASSERT_STREQ(optional.error().string().c_str(), error.string().c_str());
}

TEST(optional_test, optional_move_equal_operator_error) {
    res::error_t error{ "" };
    res::optional_t<std::string> optional = std::move(error);
    ASSERT_FALSE(optional.has_value());
    ASSERT_TRUE(optional.has_error());
    ASSERT_THROW(optional.value(), res::bad_optional_access_t);
    ASSERT_EQ(optional.error().string().size(), 0);
}

TEST(optional_test, optional_copy_value_constructor) {
    std::string value = "some error";
    res::optional_t<std::string> optional{ value };
    ASSERT_TRUE(optional.has_value());
    ASSERT_FALSE(optional.has_error());
    ASSERT_STREQ(optional.value().c_str(), value.c_str());
    ASSERT_STRNE(optional.error().string().c_str(), value.c_str());
    ASSERT_GT(optional.error().string().size(), 0);
}

TEST(optional_test, optional_move_value_constructor) {
    std::string value;
    res::optional_t<std::string> optional{ std::move(value) };
    ASSERT_TRUE(optional.has_value());
    ASSERT_FALSE(optional.has_error());
    ASSERT_EQ(optional.value().size(), 0);
    ASSERT_GT(optional.error().string().size(), 0);
}

TEST(optional_test, optional_copy_equal_operator_value) {
    std::string value = "some error";
    res::optional_t<std::string> optional = value;
    ASSERT_TRUE(optional.has_value());
    ASSERT_FALSE(optional.has_error());
    ASSERT_STREQ(optional.value().c_str(), value.c_str());
    ASSERT_STRNE(optional.error().string().c_str(), value.c_str());
    ASSERT_GT(optional.error().string().size(), 0);
}

TEST(optional_test, optional_move_equal_operator_value) {
    std::string value;
    res::optional_t<std::string> optional = std::move(value);
    ASSERT_TRUE(optional.has_value());
    ASSERT_FALSE(optional.has_error());
    ASSERT_EQ(optional.value().size(), 0);
    ASSERT_GT(optional.error().string().size(), 0);
}

TEST(optional_test, optional_copy_optional_constructor_error) {
    res::error_t error{ "some error" };
    res::optional_t<std::string> optional_1{ error };
    ASSERT_FALSE(optional_1.has_value());
    ASSERT_TRUE(optional_1.has_error());
    ASSERT_THROW(optional_1.value(), res::bad_optional_access_t);
    ASSERT_STREQ(optional_1.error().string().c_str(), error.string().c_str());

    const res::optional_t<std::string>& optional_2{ optional_1 };
    ASSERT_FALSE(optional_2.has_value());
    ASSERT_TRUE(optional_2.has_error());
    ASSERT_THROW(optional_2.value(), res::bad_optional_access_t);
    ASSERT_STREQ(
      optional_1.error().string().c_str(), optional_2.error().string().c_str());
}

TEST(optional_test, optional_copy_optional_constructor_value) {
    std::string value{ "success" };
    res::optional_t<std::string> optional_1{ value };
    ASSERT_TRUE(optional_1.has_value());
    ASSERT_FALSE(optional_1.has_error());
    ASSERT_EQ(optional_1.value(), value);
    ASSERT_GT(optional_1.error().string().size(), 0);

    const res::optional_t<std::string>& optional_2{ optional_1 };
    ASSERT_TRUE(optional_2.has_value());
    ASSERT_FALSE(optional_2.has_error());
    ASSERT_EQ(optional_1.value(), optional_2.value());
    ASSERT_STREQ(
      optional_1.error().string().c_str(), optional_2.error().string().c_str());
}

TEST(optional_test, optional_move_optional_constructor_error) {
    res::error_t error{ "some error" };
    res::optional_t<std::string> optional_1{ error };
    ASSERT_FALSE(optional_1.has_value());
    ASSERT_TRUE(optional_1.has_error());
    ASSERT_THROW(optional_1.value(), res::bad_optional_access_t);
    ASSERT_STREQ(optional_1.error().string().c_str(), error.string().c_str());

    const res::optional_t<std::string>& optional_2{ std::move(optional_1) };
    ASSERT_FALSE(optional_2.has_value());
    ASSERT_TRUE(optional_2.has_error());
    ASSERT_THROW(optional_2.value(), res::bad_optional_access_t);
    ASSERT_STREQ(optional_2.error().string().c_str(), error.string().c_str());
}

TEST(optional_test, optional_move_optional_constructor_value) {
    std::string value{ "success" };
    res::optional_t<std::string> optional_1{ value };
    ASSERT_TRUE(optional_1.has_value());
    ASSERT_FALSE(optional_1.has_error());
    ASSERT_EQ(optional_1.value(), value);
    ASSERT_GT(optional_1.error().string().size(), 0);

    const res::optional_t<std::string>& optional_2{ std::move(optional_1) };
    ASSERT_TRUE(optional_2.has_value());
    ASSERT_FALSE(optional_2.has_error());
    ASSERT_EQ(optional_2.value(), value);
    ASSERT_GT(optional_2.error().string().size(), 0);
}

TEST(optional_test, optional_copy_optional_equal_operator_error) {
    res::error_t error{ "some error" };
    res::optional_t<std::string> optional_1{ error };
    ASSERT_FALSE(optional_1.has_value());
    ASSERT_TRUE(optional_1.has_error());
    ASSERT_THROW(optional_1.value(), res::bad_optional_access_t);
    ASSERT_STREQ(optional_1.error().string().c_str(), error.string().c_str());

    const res::optional_t<std::string>& optional_2 = optional_1;
    ASSERT_FALSE(optional_2.has_value());
    ASSERT_TRUE(optional_2.has_error());
    ASSERT_THROW(optional_2.value(), res::bad_optional_access_t);
    ASSERT_STREQ(
      optional_1.error().string().c_str(), optional_2.error().string().c_str());
}

TEST(optional_test, optional_copy_optional_equal_operator_value) {
    std::string value{ "success" };
    res::optional_t<std::string> optional_1{ value };
    ASSERT_TRUE(optional_1.has_value());
    ASSERT_FALSE(optional_1.has_error());
    ASSERT_EQ(optional_1.value(), value);
    ASSERT_GT(optional_1.error().string().size(), 0);

    const res::optional_t<std::string>& optional_2 = optional_1;
    ASSERT_TRUE(optional_2.has_value());
    ASSERT_FALSE(optional_2.has_error());
    ASSERT_EQ(optional_1.value(), optional_2.value());
    ASSERT_STREQ(
      optional_1.error().string().c_str(), optional_2.error().string().c_str());
}

TEST(optional_test, optional_move_optional_equal_operator_error) {
    res::error_t error{ "some error" };
    res::optional_t<std::string> optional_1{ error };
    ASSERT_FALSE(optional_1.has_value());
    ASSERT_TRUE(optional_1.has_error());
    ASSERT_THROW(optional_1.value(), res::bad_optional_access_t);
    ASSERT_STREQ(optional_1.error().string().c_str(), error.string().c_str());

    const res::optional_t<std::string>& optional_2 = std::move(optional_1);
    ASSERT_FALSE(optional_2.has_value());
    ASSERT_TRUE(optional_2.has_error());
    ASSERT_THROW(optional_2.value(), res::bad_optional_access_t);
    ASSERT_STREQ(optional_2.error().string().c_str(), error.string().c_str());
}

TEST(optional_test, optional_move_optional_equal_operator_value) {
    std::string value{ "success" };
    res::optional_t<std::string> optional_1{ value };
    ASSERT_TRUE(optional_1.has_value());
    ASSERT_FALSE(optional_1.has_error());
    ASSERT_EQ(optional_1.value(), value);
    ASSERT_GT(optional_1.error().string().size(), 0);

    const res::optional_t<std::string>& optional_2 = std::move(optional_1);
    ASSERT_TRUE(optional_2.has_value());
    ASSERT_FALSE(optional_2.has_error());
    ASSERT_EQ(optional_2.value(), value);
    ASSERT_GT(optional_2.error().string().size(), 0);
}

TEST(optional_test, optional_pointer_operator_const_reference) {
    std::string value = "value";

    const res::optional_t<std::string> optional_1{ value };
    ASSERT_TRUE(optional_1.has_value());
    ASSERT_FALSE(optional_1.has_error());
    ASSERT_EQ(optional_1.value(), value);
    ASSERT_GT(optional_1.error().string().size(), 0);
    ASSERT_STREQ(optional_1->c_str(), value.c_str());

    const res::optional_t<std::string> optional_2{ value };
    ASSERT_TRUE(optional_2.has_value());
    ASSERT_FALSE(optional_2.has_error());
    ASSERT_EQ(optional_2.value(), value);
    ASSERT_GT(optional_2.error().string().size(), 0);
    ASSERT_STREQ(optional_2->c_str(), value.c_str());
}

TEST(optional_test, optional_pointer_operator_reference) {
    std::string value = "value";

    res::optional_t<std::string> optional_1{ value };
    ASSERT_TRUE(optional_1.has_value());
    ASSERT_FALSE(optional_1.has_error());
    ASSERT_EQ(optional_1.value(), value);
    ASSERT_GT(optional_1.error().string().size(), 0);
    ASSERT_STREQ(optional_1->c_str(), value.c_str());

    res::optional_t<std::string> optional_2{ value };
    ASSERT_TRUE(optional_2.has_value());
    ASSERT_FALSE(optional_2.has_error());
    ASSERT_EQ(optional_2.value(), value);
    ASSERT_GT(optional_2.error().string().size(), 0);
    ASSERT_STREQ(optional_2->c_str(), value.c_str());
}
