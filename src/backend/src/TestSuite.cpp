#include <include/TestSuite.hpp>

using namespace Configuration;

bool TestSuite::dynamicClassNamesAreUnique() const {
    std::unordered_set<std::string> classNames;
    classNames.reserve(files.size());

    for (const auto& file : files) {
        classNames.insert(file.getClassname());
    }

    return classNames.size() == files.size();
}

std::string TestSuite::generateGtestTypedef() const {
    const static std::string _namespace = "_" + name + "::";

    std::string result = "typedef ::testing::Types<";
    for (const auto& file : files) {
        result += _namespace + file.getClassname() + ", ";
    }
    // rm last ", "
    result.pop_back();
    result.pop_back();
    result += "> " + name + "Types;";
    return result;
}