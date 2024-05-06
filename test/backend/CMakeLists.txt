find_package(GTest REQUIRED)

enable_testing()

add_executable(
        test-gtest-typedfiles-backend
        yaml_parser.cpp
)

add_definitions(-DRES_SHARED_BASEPATH="${CMAKE_SOURCE_DIR}/test/res_shared")
add_definitions(-DPROJ_PATH="${CMAKE_SOURCE_DIR}")

target_include_directories(
        test-gtest-typedfiles-backend
        PRIVATE
        ${CMAKE_SOURCE_DIR}/src/backend/include)

target_link_libraries(
        test-gtest-typedfiles-backend
        gtest-typedfiles
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test-gtest-typedfiles-backend)
