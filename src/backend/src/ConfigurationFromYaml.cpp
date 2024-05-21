#include <include/ConfigurationFromYaml.hpp>

using namespace Configuration;

std::optional<ConfigObject> Configuration::read_from_yaml(const std::filesystem::path& path) {
    try {
        ConfigObject config;
        YAML::Node configNode = YAML::LoadFile(path.string());

        YAML::Node metaNode = configNode["meta"];
        config.resource_path = metaNode["res_path"].as<std::string>();
        config.generator_path = metaNode["generator_path"].as<std::string>();

        for (const auto& suiteNode : configNode["generator"]) {
            auto suite = suiteNode.as<TestSuite>();

            config.testsuites.push_back(suite);
        }

        return config;
    } catch (const std::exception& e) {
        spdlog::error("Failed to read configuration from {}: {}", path.string(), e.what());
    }
    return std::nullopt;
}