#pragma once

// own
#include "TestSuite.hpp"

namespace Configuration {

    /*!
     * \brief local configuration for test class generation
     */
    class ConfigObject {
    public:
        std::filesystem::path resource_path;
        std::filesystem::path generator_path;
        std::vector<TestSuite> testsuites;
    };
} // namespace Configuration
