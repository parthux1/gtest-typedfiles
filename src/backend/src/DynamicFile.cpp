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
    // ends with \n
    return returnStr;
}

std::string DynamicFile::generate(bool add_includes) const {
    std::string returnStr{};
    if (add_includes) {
        returnStr += get_includes();
    }

    returnStr += "class " + get_classname() + " {\npublic:\n";

    returnStr += tab_lines(generate_property_declaration(), 1);
    returnStr += "\n";
    returnStr += tab_lines(generate_member_declaration(), 1);
    returnStr += "\n";
    returnStr += "};\n\n";

    returnStr += generate_property_definition();
    returnStr += generate_member_definition();

    return returnStr;
}

std::string DynamicFile::generate_property_declaration() {
    return "static std::unordered_map<std::string, std::string> properties;";
}

std::string DynamicFile::generate_property_definition() const {
    std::string returnStr = "std::unordered_map<std::string, std::string> " + get_classname() + "::properties = {\n";

    const auto prop_size = properties.size();
    size_t prop_current = 0;
    for (const auto& [key, value] : properties) {
        auto temp = "{\"" + key + "\", \"" + value + "\"}";

        // comma for next line
        if (prop_current != prop_size - 1) {
            temp += ",";
        }
        if (prop_current != 0) {
            temp = "\n";
        }

        prop_current++;
        returnStr += tab_lines(temp, 1);
    }

    returnStr += "\n};\n";
    return returnStr;
}
