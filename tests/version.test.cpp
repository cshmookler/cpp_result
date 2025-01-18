// External includes
#include <gtest/gtest.h>

// Local includes
#include "../build/version.hpp"

TEST(version_test, compiletime_version_not_null) {
    ASSERT_NE(res::compiletime_version, nullptr);
}
