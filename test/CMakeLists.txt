file(GLOB test_files ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

set(TEST_EXEC "test_exec")

add_executable(${TEST_EXEC} ${test_files})

target_link_libraries(${TEST_EXEC} PRIVATE AutoGradLib)

set_property(TARGET ${TEST_EXEC} PROPERTY CXX_STANDARD 11)
