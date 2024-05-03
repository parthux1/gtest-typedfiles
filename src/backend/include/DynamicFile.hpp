#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>

namespace Configuration {
    class DynamicFile {
    public:
        //! location in file system
        std::filesystem::path path;
        //! contains custom properties
        std::unordered_map<std::string, std::string> properties;

        //! contains static members. Schema is name : (type, value)
        std::unordered_map<std::string, std::pair<std::string, std::string>> members;

        /*!
         * \brief Generate a classname for the given file.
         */
        std::string getClassname() const;

        std::string generateMemberDeclaration() const;

        std::string generateMemberDefinition() const;
    };
} // namespace Configuration
