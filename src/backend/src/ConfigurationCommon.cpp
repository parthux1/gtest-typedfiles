#include "include/ConfigurationCommon.hpp"

std::string Configuration::tab_lines(std::string lines, std::size_t tabs) {
    std::string tab_str{};
    for (std::size_t i = 0; i < tabs; ++i) {
        tab_str += "    ";
    }
    const std::string replace_str = "\n" + tab_str;
    boost::replace_all<std::string>(lines, "\n", replace_str);
    return tab_str + lines;
}