#include <ConfigurationFromYaml.hpp>
#include <gtest/gtest.h>

TEST(LoadYAML, ExampleFile) {
    const auto config = Configuration::readFromYaml(std::string(PROJ_PATH) + "/res/example_config.yaml");

    ASSERT_TRUE(config.has_value()) << "Configuration::readFromYaml failed";

    // hardcoded compare
    ASSERT_EQ(config->testSuites.size(), 1);
    const auto suite_one = config->testSuites.at(0);
    EXPECT_EQ(suite_one.name, "TestSuite1");

    ASSERT_EQ(suite_one.files.size(), 1);
    const auto file_one = suite_one.files.at(0);

    EXPECT_EQ(file_one.path, "file1.cpp");

    ASSERT_EQ(file_one.members.size(), 1);
    const auto member_one = *file_one.members.begin();

    EXPECT_EQ(member_one.first, "member1");
    EXPECT_EQ(member_one.second.first, "std::string");
    EXPECT_EQ(member_one.second.second, "\"Hello World\"");

    ASSERT_EQ(file_one.properties.size(), 1);
    const auto property_one = *file_one.properties.begin();

    EXPECT_EQ(property_one.first, "property1");
    EXPECT_EQ(property_one.second, "1");
}
