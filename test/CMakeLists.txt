set(TEST_EXEC_1 "test_exec_1")
set(TEST_EXEC_2 "test_exec_2")

add_executable(${TEST_EXEC_1} test1.cpp)
target_link_libraries(${TEST_EXEC_1} PRIVATE AutoGradLib)
set_property(TARGET ${TEST_EXEC_1} PROPERTY CXX_STANDARD 11)

add_executable(${TEST_EXEC_2} test2.cpp)
target_link_libraries(${TEST_EXEC_2} PRIVATE AutoGradLib)
set_property(TARGET ${TEST_EXEC_2} PROPERTY CXX_STANDARD 11)
