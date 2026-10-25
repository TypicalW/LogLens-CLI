# CMake generated Testfile for 
# Source directory: /home/typicalw/Code/LogLens
# Build directory: /home/typicalw/Code/LogLens/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(LogLensSmokeTest "/home/typicalw/Code/LogLens/build/loglens_tests")
set_tests_properties(LogLensSmokeTest PROPERTIES  _BACKTRACE_TRIPLES "/home/typicalw/Code/LogLens/CMakeLists.txt;33;add_test;/home/typicalw/Code/LogLens/CMakeLists.txt;0;")
add_test(LogLensAnalyzerTest "/home/typicalw/Code/LogLens/build/loglens_analyzer_tests")
set_tests_properties(LogLensAnalyzerTest PROPERTIES  _BACKTRACE_TRIPLES "/home/typicalw/Code/LogLens/CMakeLists.txt;46;add_test;/home/typicalw/Code/LogLens/CMakeLists.txt;0;")
add_test(LogLensFilterTest "/home/typicalw/Code/LogLens/build/loglens_filter_tests")
set_tests_properties(LogLensFilterTest PROPERTIES  _BACKTRACE_TRIPLES "/home/typicalw/Code/LogLens/CMakeLists.txt;57;add_test;/home/typicalw/Code/LogLens/CMakeLists.txt;0;")
