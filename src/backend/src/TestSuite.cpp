#include <include/TestSuite.hpp>

using namespace Configuration;

bool TestSuite::dynamicClassNamesAreUnique() const {
    std::unordered_set<std::string> classNames;
    classNames.reserve(files.size());

    for (const auto& file : files) {
        classNames.insert(file.getClassname());
    }

    return classNames.size() == files.size();
}

std::string TestSuite::generateGtestTypedef() const {
    const static std::string _namespace = getNamespace() + "::";

    std::string result = "typedef ::testing::Types<";
    for (const auto& file : files) {
        result += _namespace + file.getClassname() + ", ";
    }
    // rm last ", "
    result.pop_back();
    result.pop_back();
    result += "> " + name + "Types;";
    return result;
}

std::string TestSuite::wrapInNamespace(const std::string& content) const {
    return "namespace " + getNamespace() + " {\n" + content + "}\n";
}
std::string TestSuite::getNamespace() const { return "_" + name; }

bool TestSuite::generateDynFilesOnDisk(const std::filesystem::path& folderPath, bool overwrite,
                                       bool fail_on_skip) const {

    bool all_files_generated = true; // will be toggled if file generation is skipped.
    std::vector<std::filesystem::path> generatedFiles{};
    auto cleanup = [&generatedFiles]() {
        spdlog::debug("Cleaning up generated files.");
        for (const auto& file : generatedFiles) {
            std::filesystem::remove(file);
        }
    };

    // create dir if its missing but register it for deletion if function failes
    if (!folderPath.has_extension() && !std::filesystem::exists(folderPath)) {
        spdlog::debug("Creating {}", folderPath.string());
        std::filesystem::create_directory(folderPath);
        generatedFiles.push_back(folderPath);
    }

    if (!std::filesystem::is_directory(folderPath)) {
        spdlog::debug("folderPath({}) is not a directory.", folderPath.string());
        return false;
    }

    if (!std::filesystem::exists(folderPath)) {
        spdlog::debug("Path({}) does not exist.", folderPath.string());
        return false;
    }

    try {
        for (const auto& file : files) {
            const auto content = wrapInNamespace(file.generate());
            const auto path = folderPath / file.path;

            if (std::filesystem::exists(path) && !overwrite) {
                spdlog::warn("File {} already exists. Skipping.", path.string());
                all_files_generated = false;
                continue;
            }
            // register this file for cleanup if this function fails
            generatedFiles.push_back(path);
            std::fstream fs(path, std::ios::out | std::ios::trunc);
            if (!fs.is_open()) {
                spdlog::error("Could not open file {}", path.string());
                throw std::runtime_error("Could not open file");
            }

            fs << content;
            fs.close();
            spdlog::debug("Generated file {}", path.string());
        }
    }
    // cleanup generated files
    catch (const std::exception& e) {
        cleanup();
        return false;
    }

    if (!all_files_generated && fail_on_skip) {
        cleanup();
        return false;
    }

    return true;
}
