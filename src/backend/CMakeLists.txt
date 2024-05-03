set(HEADERS
        include/Configuration.hpp
        include/ConfigurationFromYaml.hpp
        include/TestSuite.hpp
        include/DynamicFile.hpp
)

set(SRC
        src/Configuration.cpp
        src/DynamicFile.cpp
        src/TestSuite.cpp
        src/ConfigurationFromYaml.cpp
)

add_library(gtest-typedfiles STATIC
        ${SRC}
        ${HEADERS}
)

find_package(yaml-cpp REQUIRED)
find_package(spdlog REQUIRED)

target_link_libraries(gtest-typedfiles PUBLIC
        yaml-cpp::yaml-cpp
        spdlog::spdlog
)

target_include_directories(gtest-typedfiles PUBLIC .)