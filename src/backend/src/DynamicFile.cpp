#include <include/DynamicFile.hpp>

using namespace Configuration;

std::string DynamicFile::get_classname() const {
    std::string filename = path.filename();
    if (path.has_extension()) {
        const std::size_t ext_length = path.extension().string().length();
        filename = filename.substr(0, filename.size() - ext_length);
    }

    return filename;
}

std::string DynamicFile::get_includes() const { return "#include <unordered_map>\n#include <string>\n"; }

std::string DynamicFile::generate_member_declaration() const {

    std::string returnStr{};

    for (const auto& [name, member] : members) {
        const std::string type = member.first;
        const auto addition = "static " + type + " " + name + ";\n";
        returnStr += addition;
    }

    return returnStr;
}
std::string DynamicFile::generate_member_definition() const {
    std::string returnStr{};

    for (const auto& [name, member] : members) {
        const std::string type = member.first;
        const std::string value = member.second;
        const auto addition = type + " " + get_classname() + "::" + name + " = " + value + ";\n";
        returnStr += addition;
    }

    return returnStr;
}
std::string DynamicFile::generate(bool add_includes) const {
    std::string returnStr{};
    if (add_includes) {
        returnStr += get_includes();
    }

    returnStr += "class " + get_classname() + " {\npublic:\n";

    returnStr += generate_property_declaration();
    returnStr += generate_member_declaration();
    returnStr += "};\n";

    returnStr += generate_property_definition();
    returnStr += generate_member_definition();

    return returnStr;
}
std::string DynamicFile::generate_property_declaration() {
    return "static std::unordered_map<std::string, std::string> properties;\n";
}
std::string DynamicFile::generate_property_definition() const {
    std::string returnStr = "std::unordered_map<std::string, std::string> " + get_classname() + "::properties = {\n";

    for (const auto& [key, value] : properties) {
        returnStr += "    {\"" + key + "\", \"" + value + "\"},\n";
    }

    returnStr += "};\n";
    return returnStr;
}
