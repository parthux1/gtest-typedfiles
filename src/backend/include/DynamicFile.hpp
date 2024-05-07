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

        /*!
         * \brief Generate static member declarations for the given file. All generated lines are escaped with a \n
         */
        std::string generateMemberDeclaration() const;

        /*!
         * \brief Generate static member definitions for the given file. All generated lines are escaped with a \n
         */
        std::string generateMemberDefinition() const;

        /*!
         * \brief Generate the property declaration for the given file.
         * This is a simple std::unordered_map<std::string, std::string>
         */
        static std::string generatePropertyDeclaration();

        /*!
         * \brief Generate the property definition for the given file.
         */
        std::string generatePropertyDefinition() const;

        /*!
         * \brief Generates the class definition followed by initializing static members.
         */
        std::string generate() const;
    };
} // namespace Configuration
