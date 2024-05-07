#pragma once

#include <string>
#include <unordered_set>
#include <vector>
// own
#include "DynamicFile.hpp"

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

    private:
        /*!
         * \brief Generate the namespace-name for the current test suite.
         */
        [[nodiscard]] std::string getNamespace() const;
    };

} // namespace Configuration
