add_executable(gtest-typedfiles-cli main.cpp)

find_package(spdlog REQUIRED)
target_link_libraries(gtest-typedfiles-cli PUBLIC
        spdlog::spdlog
        gtest-typedfiles)