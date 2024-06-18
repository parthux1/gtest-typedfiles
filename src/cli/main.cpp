#include <iostream>

// own
#include <include/ConfigurationFromYaml.hpp>

// 3rd party
#include <boost/program_options.hpp>
#include <spdlog/spdlog.h>

namespace po = boost::program_options;

/*!
 * \brief function run as soon as cli arguments are parsed and env is ready
 * \param vm
 * \return
 */
int cli_main(const po::variables_map& vm) {
    // parse config
    const auto CLI_CONFIG_PATH = vm.at("config").as<std::string>();
    const auto CONFIG = Configuration::read_from_yaml(CLI_CONFIG_PATH);

    if (!CONFIG.has_value()) {
        return 1;
    }

    // generate dynamic files
    const auto CLI_TARGET_PATH = vm.at("result-folder").as<std::string>();
    auto testSuite = CONFIG->testsuites[0];
    const auto RES_DYN = testSuite.generate_dynfiles_on_disk(CLI_TARGET_PATH, true, true);
    spdlog::info("Dyn-Generation: {}", RES_DYN.has_value() ? "successful" : "failed");

    // generate include header
    const auto RES_INCLUDE = testSuite.generate_includefile_on_disk(CLI_TARGET_PATH, true);
    spdlog::info("Inc-Generation: {}", RES_INCLUDE ? "successful" : "failed");

    return 0;
}

void display_help(char* const* av, po::positional_options_description& pos_opts, po::options_description& vis_opts) {
    // required arguments
    const auto program_name = std::filesystem::path(av[0]).filename().string();
    std::cout << "Arguments:\n" << program_name;

    for (int i = 0; i < pos_opts.max_total_count(); i++) {
        std::cout << " [" << pos_opts.name_for_position(i) << "]";
    }

    // optional arguments
    std::cout << "\n\n";
    std::cout << vis_opts << "\n";
}

/*!
 * \brief main function handles argument parser setup & environment settings
 */
int main(int ac, char** av) {

    // pinning down required options
    po::positional_options_description pos_opts;
    pos_opts.add("config", 1).add("result-folder", 1);

    // required arguments | invisible options
    po::options_description inv_opts("Required options");
    inv_opts.add_options()("config", "path to a configuration file.")("result-folder", po::value<std::string>(),
                                                                      "path to the target directory to write to");

    // visible options
    po::options_description vis_opts("Optional arguments");
    vis_opts.add_options()("help", "display this message")("log-level", po::value<std::string>()->default_value("info"),
                                                           "one of: debug, info, off");

    // concat options
    po::options_description cmdline_options;
    cmdline_options.add(inv_opts).add(vis_opts);

    // parse args
    po::variables_map vm;
    po::store(po::command_line_parser(ac, av).positional(pos_opts).options(cmdline_options).run(), vm);

    for (const auto& [key, value] : vm) {
        spdlog::info("Key: {}", key);
    }

    // help msg if default is missing or --help is specified
    bool required_arg_missing = false;
    for (std::size_t i = 0; i < pos_opts.max_total_count(); i++) {
        const auto name = pos_opts.name_for_position(i);
        if (!vm.count(name)) {
            required_arg_missing = true;
            break;
        }
    }

    if (vm.count("help") || required_arg_missing) {
        display_help(av, pos_opts, vis_opts);
        return 0;
    }

    // maybe raise unknown errors
    po::notify(vm);

    // set log level
    auto level = spdlog::level::info;
    if (vm.count("log-level")) {
        const auto CLI_LOG_LEVEL = vm.at("log-level").as<std::string>();

        if (CLI_LOG_LEVEL == "debug") {
            level = spdlog::level::debug;
        } else if (CLI_LOG_LEVEL == "info") {
            // default of variable
            ;
        } else if (CLI_LOG_LEVEL == "off") {
            level = spdlog::level::off;
        } else {
            spdlog::error("Invalid log-level: {}. Defaulting to info", CLI_LOG_LEVEL);
        }
    }
    spdlog::set_level(level);

    return cli_main(vm);
}
