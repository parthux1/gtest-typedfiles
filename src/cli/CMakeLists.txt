add_executable(gtest-typedfiles-cli main.cpp)

find_package(spdlog REQUIRED)
find_package(Boost REQUIRED COMPONENTS program_options)

target_link_libraries(gtest-typedfiles-cli PUBLIC
        spdlog::spdlog
        gtest-typedfiles
        Boost::program_options)