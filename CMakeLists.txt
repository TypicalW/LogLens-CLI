cmake_minimum_required(VERSION 3.16)

project(LogLens VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(loglens
    src/main.cpp
    src/log_parser.cpp
    src/log_reader.cpp
    src/log_analyzer.cpp
    src/log_filter.cpp
)

target_include_directories(loglens PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

enable_testing()

add_executable(loglens_tests
    tests/test_smoke.cpp
    src/log_parser.cpp
)

target_include_directories(loglens_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_test(NAME LogLensSmokeTest COMMAND loglens_tests)

add_executable(loglens_analyzer_tests
    tests/test_analyzer.cpp
    src/log_parser.cpp
    src/log_reader.cpp
    src/log_analyzer.cpp
)

target_include_directories(loglens_analyzer_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_test(NAME LogLensAnalyzerTest COMMAND loglens_analyzer_tests)

add_executable(loglens_filter_tests
    tests/test_filter.cpp
    src/log_filter.cpp
)

target_include_directories(loglens_filter_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_test(NAME LogLensFilterTest COMMAND loglens_filter_tests)