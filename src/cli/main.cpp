// own
#include <include/ConfigurationFromYaml.hpp>
// 3rd party
#include <spdlog/spdlog.h>

constexpr auto TARGET_PATH = "./generated";

int main() {
    spdlog::set_level(spdlog::level::debug);
    const auto config = Configuration::readFromYaml("../../../res/example_config.yaml");
    spdlog::info("Config: {}", config.has_value() ? "valid" : "invalid");

    auto testSuite = config->testSuites[0];
    const auto res_dyn = testSuite.generate_dynfiles_on_disk(TARGET_PATH, true, true);
    spdlog::info("Dyn-Generation: {}", res_dyn.has_value() ? "successful" : "failed");

    const auto res_include = testSuite.generate_includefile_on_disk(TARGET_PATH, true);
    spdlog::info("Inc-Generation: {}", res_include ? "successful" : "failed");

    return 0;
}