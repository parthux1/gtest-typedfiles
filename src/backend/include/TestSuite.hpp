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
        [[nodiscard]] bool dynamicClassNamesAreUnique() const;

        /*!
         * \brief generate ::testing::Types aggregation
         */
        [[nodiscard]] std::string generateGtestTypedef() const;

        [[nodiscard]] std::string wrapInNamespace(const std::string& content) const;

        /*!
         * \brief generate all stored DynamicFiles and save them on disk
         * \param folderPath must be a valid path to a folder. The folder is only dynamically created if has no
         * extension r"*.*"
         * \param overwrite if true, existing files will be overwritten
         * \param fail_on_skip if true, the function will fail if a file could not be generated
         * \note if this function fails it tries to erase all maybe stored files.
         * \return true if successful
         */
        [[nodiscard]] bool generateOnDisk(const std::filesystem::path& folderPath, bool overwrite = false,
                                          bool fail_on_skip = true) const;

    private:
        /*!
         * \brief Generate the namespace-name for the current test suite.
         */
        [[nodiscard]] std::string getNamespace() const;
    };

} // namespace Configuration
