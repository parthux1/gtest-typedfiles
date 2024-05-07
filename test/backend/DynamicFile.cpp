#include <DynamicFile.hpp>
#include <gtest/gtest.h>

TEST(DynamicFile, getClassname) {
    Configuration::DynamicFile file;

    auto check_path = [&file](std::string_view path, std::string_view expected) {
        file.path = path;
        ASSERT_EQ(file.getClassname(), expected);
    };

    check_path("missing/value", "value");
    check_path("value.missing", "value");
    check_path(" +_-~*", " +_-~*");
}

TEST(DynamicFile, generateMemberDeclaration) {
    Configuration::DynamicFile file;

    file.members["member1"] = {"std::string", "val1"};
    ASSERT_EQ(file.generateMemberDeclaration(), "static std::string member1;\n");

    file.members["member2"] = {"int", "42"};
    const auto result = file.generateMemberDeclaration();
    ASSERT_TRUE(result.find("std::string member1;\n") != std::string::npos);
    ASSERT_TRUE(result.find("int member2;\n") != std::string::npos);
}

TEST(DynamicFile, generateMemberDefinition) {
    Configuration::DynamicFile file;

    file.members["member1"] = {"std::string", "\"val1\""};
    ASSERT_EQ(file.generateMemberDefinition(), "std::string ::member1 = \"val1\";\n");

    file.members["member2"] = {"int", "42"};
    const auto result = file.generateMemberDefinition();
    ASSERT_TRUE(result.find("std::string ::member1 = \"val1\";\n") != std::string::npos);
    ASSERT_TRUE(result.find("int ::member2 = 42;\n") != std::string::npos);

    file.members.clear();
    file.path = "MyClass";
    file.members["member1"] = {"int", "1"};
    ASSERT_EQ(file.generateMemberDefinition(), "int MyClass::member1 = 1;\n");
}