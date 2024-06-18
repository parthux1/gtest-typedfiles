#include <gtest/gtest.h>
#include <include/ConfigurationCommon.hpp>
TEST(ConfigurationCommon, tab_lines) {
    const std::string input = "line 1\nline2\nline3";
    const std::string res = Configuration::tab_lines(input, 2);
    const std::string expected = "\t\tline 1\n\t\tline2\n\t\tline3";

    ASSERT_EQ(res, expected);
}