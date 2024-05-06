// own
#include <include/ConfigurationFromYaml.hpp>
// 3rd party
#include <spdlog/spdlog.h>

constexpr auto TARGET_PATH = "/generated/";

int main() {

    const auto config = Configuration::readFromYaml("../../../res/example_config.yaml");
    spdlog::info("Config: {}", config.has_value() ? "valid" : "invalid");

    for (const auto& suite : config->testSuites) {
        spdlog::info("Suite: {}", suite.name);
        for (const auto& file : suite.files) {
            spdlog::info(file.generateMemberDeclaration());
            spdlog::info(file.generateMemberDefinition());
        }

        spdlog::info(suite.generateGtestTypedef());
    }
    return 0;
}