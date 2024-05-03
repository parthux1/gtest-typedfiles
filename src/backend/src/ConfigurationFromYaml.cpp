#include <include/ConfigurationFromYaml.hpp>

using namespace Configuration;

std::optional<ConfigObject> Configuration::readFromYaml(const std::filesystem::path& path) {
    try {
        ConfigObject config;
        YAML::Node configNode = YAML::LoadFile(path.string());

        YAML::Node metaNode = configNode["meta"];
        config.resourcePath = metaNode["res_path"].as<std::string>();
        config.generatorPath = metaNode["generator_path"].as<std::string>();

        for (const auto& suiteNode : configNode["generator"]) {
            auto suite = suiteNode.as<TestSuite>();

            config.testSuites.push_back(suite);
        }

        return config;
    } catch (const std::exception& e) {
        spdlog::error("Failed to read configuration from {}: {}", path.string(), e.what());
    }
    return std::nullopt;
}