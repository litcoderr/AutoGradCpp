set(LIB_NAME "AutoGradLib")

file(GLOB_RECURSE autograd_cpp_files *.cpp)
file(GLOB_RECURSE autograd_hpp_files *.hpp)

add_library(${LIB_NAME} ${autograd_cpp_files} ${autograd_hpp_files})
set_property(TARGET ${LIB_NAME} PROPERTY CXX_STANDARD 11)

target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
