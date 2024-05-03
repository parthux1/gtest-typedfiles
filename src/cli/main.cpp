// own
#include <include/ConfigurationFromYaml.hpp>
// 3rd party
#include <spdlog/spdlog.h>

int main() {

    const auto config = Configuration::readFromYaml("../../../res/example_config.yaml");
    spdlog::info("Config: {}", config.has_value() ? "valid" : "invalid");

    spdlog::info(config->testSuites[0].generateGtestTypedef());
    return 0;
}