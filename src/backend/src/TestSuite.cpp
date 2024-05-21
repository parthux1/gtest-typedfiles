#include <include/TestSuite.hpp>

using namespace Configuration;

bool TestSuite::dynamic_classnames_are_unique() const {
    std::unordered_set<std::string> classNames;
    classNames.reserve(files.size());

    for (const auto& file : files) {
        classNames.insert(file.getClassname());
    }

    return classNames.size() == files.size();
}

std::string TestSuite::generate_gtest_typedef() const {
    const static std::string _namespace = get_namespace() + "::";

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

std::string TestSuite::wrap_in_namespace(const std::string& content) const {
    return "namespace " + get_namespace() + " {\n" + content + "}\n";
}

std::string TestSuite::get_namespace() const { return "_" + name; }

std::optional<std::vector<std::filesystem::path>>
TestSuite::generate_dynfiles_on_disk(const std::filesystem::path& folder_path, bool overwrite,
                                     bool fail_on_skip) const {

    bool all_files_generated = true; // will be toggled if file generation is skipped.
    std::vector<std::filesystem::path> generated_files{};
    std::optional<std::filesystem::path> folder_to_delete = std::nullopt;

    // create dir if its missing but register it for deletion if function fails
    if (create_folder_if_no_extension_and_missing(folder_path)) {
        folder_to_delete = folder_path;
    }

    if (!std::filesystem::is_directory(folder_path)) {
        spdlog::debug("folder_path({}) is not a directory.", folder_path.string());
        cleanup(generated_files, folder_to_delete);
        return std::nullopt;
    }

    // breaks prematurely if a file could not be generated, but we expected it to be
    for (const auto& file : files) {

        // we explicitly generate includes outside the namespace
        const auto content = file.getIncludes() + wrap_in_namespace(file.generate(false));
        const auto path = folder_path / file.path;

        const auto file_exists = std::filesystem::exists(path);
        if (file_exists && !overwrite) {
            spdlog::warn("File {} already exists. Skipping.", path.string());
            all_files_generated = false;
            continue;
        }
        // register this file for cleanup if this function fails
        generated_files.push_back(path);

        const bool success = write_to_disk(path, content);
        if (!success) {
            cleanup(generated_files, folder_to_delete);
            return std::nullopt;
        }
    }

    if (!all_files_generated && fail_on_skip) {
        cleanup(generated_files, folder_to_delete);
        return std::nullopt;
    }

    return generated_files;
}

bool TestSuite::generate_includefile_on_disk(const std::filesystem::path& folder_path, bool overwrite) const {

    std::vector<std::filesystem::path> generatedFiles{};
    std::optional<std::filesystem::path> folder_to_delete = std::nullopt;

    if (create_folder_if_no_extension_and_missing(folder_path)) {
        folder_to_delete = folder_path;
    }

    if (!std::filesystem::is_directory(folder_path)) {
        spdlog::debug("folder_path({}) is not a directory.", folder_path.string());
        cleanup(generatedFiles, folder_to_delete);
        return false;
    }
    std::string content{};

    // include all files
    for (const auto& file : files) {
        content += "#include \"" + file.path.string() + "\"\n";
    }
    content += generate_gtest_typedef();

    if (!write_to_disk(folder_path / (name + ".hpp"), content)) {
        cleanup(generatedFiles, folder_to_delete);
        return false;
    }
    return true;
}

bool TestSuite::create_folder_if_no_extension_and_missing(const std::filesystem::path& folder_path) {
    if (folder_path.has_extension() || std::filesystem::exists(folder_path)) {
        spdlog::debug("Not generating '{}' because Extension: {} || Exists: {}", folder_path.string(),
                      folder_path.has_extension(), std::filesystem::exists(folder_path));
        return false;
    }

    spdlog::debug("Creating {}", folder_path.string());
    std::filesystem::create_directory(folder_path);
    return true;
}

void TestSuite::cleanup(const std::vector<std::filesystem::path>& remove_list,
                        std::optional<std::filesystem::path> folder) {

    spdlog::info("Cleaning up generated files.");
    for (const auto& file : remove_list) {
        spdlog::debug("Deleting {}", file.string());
        const bool success = std::filesystem::remove(file);

        if (!success) {
            spdlog::warn("Could not delete {}", file.string());
        }
    };

    if (folder.has_value()) {
        spdlog::debug("Deleting folder {}", folder.value().string());
        const bool success = std::filesystem::remove(folder.value());
        if (!success) {
            spdlog::warn("Could not delete {}", folder.value().string());
        }
    }
}

bool TestSuite::write_to_disk(const std::filesystem::path& path, const std::string& content) {
    const auto file_exists = std::filesystem::exists(path);

    std::fstream fs(path, std::ios::out | std::ios::trunc);
    if (!fs.is_open()) {
        spdlog::error("Could not open file {}", path.string());
        return false;
    }

    fs << content;
    fs.close();

    // log what happened
    if (file_exists) {
        spdlog::debug("Replaced file {}", path.string());
    } else {
        spdlog::debug("Generated file {}", path.string());
    }

    return true;
}
