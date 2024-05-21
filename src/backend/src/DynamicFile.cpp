#include <include/DynamicFile.hpp>

using namespace Configuration;

std::string DynamicFile::getClassname() const {
    std::string filename = path.filename();
    if (path.has_extension()) {
        const std::size_t ext_length = path.extension().string().length();
        filename = filename.substr(0, filename.size() - ext_length);
    }

    return filename;
}

std::string DynamicFile::getIncludes() const { return "#include <unordered_map>\n#include <string>\n"; }

std::string DynamicFile::generateMemberDeclaration() const {

    std::string returnStr{};

    for (const auto& [name, member] : members) {
        const std::string type = member.first;
        const auto addition = "static " + type + " " + name + ";\n";
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
std::string DynamicFile::generate(bool add_includes) const {
    std::string returnStr{};
    if (add_includes) {
        returnStr += getIncludes();
    }

    returnStr += "class " + getClassname() + " {\npublic:\n";

    returnStr += generatePropertyDeclaration();
    returnStr += generateMemberDeclaration();
    returnStr += "};\n";

    returnStr += generatePropertyDefinition();
    returnStr += generateMemberDefinition();

    return returnStr;
}
std::string DynamicFile::generatePropertyDeclaration() {
    return "static std::unordered_map<std::string, std::string> properties;\n";
}
std::string DynamicFile::generatePropertyDefinition() const {
    std::string returnStr = "std::unordered_map<std::string, std::string> " + getClassname() + "::properties = {\n";

    for (const auto& [key, value] : properties) {
        returnStr += "    {\"" + key + "\", \"" + value + "\"},\n";
    }

    returnStr += "};\n";
    return returnStr;
}
