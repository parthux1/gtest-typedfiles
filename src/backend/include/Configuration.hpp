#pragma once

// own
#include "TestSuite.hpp"

namespace Configuration {

    /*!
     * \brief local configuration for test class generation
     */
    class ConfigObject {
    public:
        std::filesystem::path resourcePath;
        std::filesystem::path generatorPath;
        std::vector<TestSuite> testSuites;
    };
} // namespace Configuration
