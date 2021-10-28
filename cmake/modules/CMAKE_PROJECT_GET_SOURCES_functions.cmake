# CMAKE_PROJECT_GET_SOURCES_functions.cmake
cmake_minimum_required(VERSION 3.13)

function(say_path_to_cmake)
    message("processing CMakelists.txt: ${CMAKE_CURRENT_LIST_DIR}")
endfunction()

function(say_path_to_root_cmake)
    message("processing CMakelists.txt: ${CMAKE_CURRENT_LIST_DIR} <ROOT>")
endfunction()