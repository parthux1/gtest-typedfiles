find_package(GTest REQUIRED)

enable_testing()

add_executable(
        test-gtest-typedfiles-backend
        yaml_parser.cpp
)

add_definitions(-DRES_SHARED_BASEPATH="${CMAKE_SOURCE_DIR}/test/res_shared/")

target_include_directories(
        test-gtest-typedfiles-backend
        PRIVATE
        ${CMAKE_SOURCE_DIR}/src/backend/include)

target_link_libraries(
        test-gtest-typedfiles-backend
        gtest-typedfiles
        GTest::GTestMain
)

include(GoogleTest)
gtest_discover_tests(feed-spec-lib-test)
