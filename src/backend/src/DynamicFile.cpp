#include <include/DynamicFile.hpp>

using namespace Configuration;

std::string DynamicFile::getClassname() const {
    std::string filename = path.filename();
    if (path.has_extension()) {
        const std::size_t length = path.extension().string().length();
        filename = filename.substr(0, length);
    }

    return filename;
}
std::string DynamicFile::generateMemberDeclaration() const {

    std::string returnStr{};

    for (const auto& [name, member] : members) {
        const std::string type = member.first;
        const auto addition = type + " " + name + ";";
        returnStr += addition;
    }

    return returnStr;
}
std::string DynamicFile::generateMemberDefinition() const {
    std::string returnStr{};

    for (const auto& [name, member] : members) {
        const std::string type = member.first;
        const std::string value = member.second;
        const auto addition = type + " " + getClassname() + "::" + name + " = " + value + ";\n";
        returnStr += addition;
    }

    return returnStr;
}
