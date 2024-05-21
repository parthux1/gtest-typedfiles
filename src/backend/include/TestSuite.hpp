#pragma once

#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>
// own
#include "DynamicFile.hpp"

// 3rd party
#include <spdlog/spdlog.h>

namespace Configuration {

    class TestSuite {
    public:
        //! name of the test suite
        std::string name;
        //! list of files in the test suite
        std::vector<DynamicFile> files;

        /*!
         * \brief Check whether to-be generated classnames in stored DynamicFiles are unique.
         */
        [[nodiscard]] bool dynamic_classnames_are_unique() const;

        /*!
         * \brief generate ::testing::Types aggregation
         */
        [[nodiscard]] std::string generate_gtest_typedef() const;

        [[nodiscard]] std::string wrap_in_namespace(const std::string& content) const;

        /*!
         * \brief generate all stored DynamicFiles and save them on disk
         * \param folder_path must be a valid path to a folder. The folder is only dynamically created if has no
         * extension r"*.*"
         * \param overwrite if true, existing files will be overwritten
         * \param fail_on_skip if true, the function will fail if a file could not be generated
         * \note if this function fails it tries to erase all maybe stored files.
         * \returns a list of all generated files on success.
         */
        [[nodiscard]] std::optional<std::vector<std::filesystem::path>>
        generate_dynfiles_on_disk(const std::filesystem::path& folder_path, bool overwrite = false,
                                  bool fail_on_skip = true) const;
        /*!
         * \brief generate an include able file importing all DynFiles and defining the test suites typing.
         * \param folder_path must be a valid path to a folder. The folder is only dynamically created if has no
         * extension r"*.*"
         * \param overwrite if true, the existing file will be overwritten
         * \return true if successful
         */
        [[nodiscard]] bool generate_includefile_on_disk(const std::filesystem::path& folder_path,
                                                        bool overwrite = false) const;

        /*!
         * \brief generate all files from this test suite on disk.
         * \returns true if successful
         */
        [[nodiscard]] bool generate() const;

    private:
        /*!
         * \brief Generate the namespace-name for the current test suite.
         */
        [[nodiscard]] std::string get_namespace() const;

        /*!
         * \brief Create a folder if the given folder_path has no extension and does not already exist.
         * \return true if the folder was generated
         */
        static bool create_folder_if_no_extension_and_missing(const std::filesystem::path& folder_path);

        /*!
         * \brief Delete all mentioned files and folders.
         * \param remove_list all referenced files will be deleted.
         * \param folders all referenced files will be deleted. additional param for better readability, the usage.
         */
        static void cleanup(const std::vector<std::filesystem::path>& remove_list,
                            std::optional<std::filesystem::path> folder);

        /*!
         * \brief Write to disk using std::ios::out | std::ios::trunc
         * \param path the path to the file
         * \param content what to write
         * \returns true if successful
         */
        static bool write_to_disk(const std::filesystem::path& path, const std::string& content);
    };

} // namespace Configuration
