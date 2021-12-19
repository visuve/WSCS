cmake_minimum_required(VERSION 3.16)

project("wscs")

set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(C_STANDARD_REQUIRED ON)

if(MSVC)
	add_compile_options(/W4 /WX /MP)
else()
	add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

set(EXECUTABLE_OUTPUT_PATH "..")
set(LIBRARY_OUTPUT_PATH "..")

add_subdirectory("wshf2")
add_subdirectory("wsbc512")
add_subdirectory("tests")