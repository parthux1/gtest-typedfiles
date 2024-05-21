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
        std::string get_classname() const;

        /*!
         * \brief Generate the includes for the given file. All generated lines are escaped with a \n
         */
        std::string get_includes() const;

        /*!
         * \brief Generate static member declarations for the given file. All generated lines are escaped with a \n
         */
        std::string generate_member_declaration() const;

        /*!
         * \brief Generate static member definitions for the given file. All generated lines are escaped with a \n
         */
        std::string generate_member_definition() const;

        /*!
         * \brief Generate the property declaration for the given file.
         * This is a simple std::unordered_map<std::string, std::string>
         */
        static std::string generate_property_declaration();

        /*!
         * \brief Generate the property definition for the given file.
         */
        std::string generate_property_definition() const;

        /*!
         * \brief Generates the class definition followed by initializing static members.
         * \param add_includes if true, includes are added to the generated string.
         */
        std::string generate(bool add_includes = true) const;
    };
} // namespace Configuration
