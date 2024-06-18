#pragma once
#include <boost/algorithm/string/replace.hpp>

namespace Configuration {
    /*!
     * \brief Append tabs to each line in a string
     * \param lines string to edit
     * \param tabs amount of tabs to add
     * \return modified string
     */
    std::string tab_lines(std::string lines, std::size_t tabs = 1);
} // namespace Configuration
