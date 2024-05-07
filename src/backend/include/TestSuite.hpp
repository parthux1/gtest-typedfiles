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
    };

} // namespace Configuration
