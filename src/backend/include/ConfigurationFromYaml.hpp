#pragma once
#include <cassert>
#include <filesystem>
#include <optional>
// own
#include "Configuration.hpp"

// 3rd party
#include <spdlog/spdlog.h>
#include <yaml-cpp/yaml.h>

// Implement yaml IO for Configuration:: classes

namespace YAML {
    template <> struct convert<Configuration::TestSuite> {
        static Node encode(const Configuration::TestSuite& rhs) {
            Node node;
            node["testsuite"] = rhs.name;
            // TODO: handle DynamicFile
            return node;
        }

        static bool decode(const Node& node, Configuration::TestSuite& rhs) {
            rhs.name = node["testsuite"].as<std::string>();
            rhs.files.reserve(node["files"].size());

            for (const auto& fileNode : node["files"]) {
                const auto file = fileNode.as<Configuration::DynamicFile>();
                rhs.files.push_back(file);
            }
            return true;
        }
    };

    template <> struct convert<Configuration::DynamicFile> {
        static Node encode(const Configuration::DynamicFile& rhs) {
            Node node;
            node.begin()->first = rhs.path.string();
            for (const auto& [name, member] : rhs.members) {
                Node memberNode;
                memberNode["name"] = name;
                memberNode["type"] = member.first;
                memberNode["value"] = member.second;
                node["members"].push_back(memberNode);
            }
            for (const auto& [key, val] : rhs.properties) {
                node["properties"][key] = val;
            }

            return node;
        }

        static bool decode(const Node& node, Configuration::DynamicFile& rhs) {

            // first key is path
            rhs.path = node.begin()->first.as<std::string>();

            for (const auto& memberNode : node["members"]) {
                // grab member name
                auto it = memberNode.begin();
                const auto key = it->first.as<std::string>();

                // grab type and value
                auto& list_node = it->second;
                assert(list_node.IsSequence());
                auto it_list_node = list_node.begin();
                const auto type = it_list_node++->as<std::string>();
                const auto val = it_list_node->as<std::string>();

                rhs.members[key] = {type, val};
            }

            // copy properties
            for (const auto& propNode : node["properties"]) {
                const auto key = propNode.begin()->first.as<std::string>();
                const auto val = propNode.begin()->second.as<std::string>();
                rhs.properties[key] = val;
            }

            return true;
        }
    };
} // namespace YAML

namespace Configuration {
    /*!
     * \brief Try to build a configuration object from a yaml.
     */
    [[nodiscard]] std::optional<ConfigObject> read_from_yaml(const std::filesystem::path& path);
} // namespace Configuration
