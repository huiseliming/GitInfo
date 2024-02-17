
if(NOT DEFINED GIT_EXECUTABLE)
    find_package(Git QUIET REQUIRED)
endif()
if(NOT DEFINED GIT_EXECUTABLE)
    message(FATAL_ERROR "The \"${GIT_EXECUTABLE}\" variable must be defined.")
endif()
get_filename_component(GIT_EXECUTABLE "${GIT_EXECUTABLE}" ABSOLUTE)

macro(RunGitCommand)
    execute_process(COMMAND
        "${GIT_EXECUTABLE}" ${ARGV}
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
        RESULT_VARIABLE LAST_GIT_EXIT_CODE
        OUTPUT_VARIABLE LAST_GIT_OUTPUT
        ERROR_VARIABLE stderr
        OUTPUT_STRIP_TRAILING_WHITESPACE)
    if(NOT LAST_GIT_EXIT_CODE EQUAL 0)
        string(REPLACE ";" " " args_with_spaces "${ARGV}")
        message(FATAL_ERROR "${stderr} (${GIT_EXECUTABLE} ${args_with_spaces})")
    endif()
endmacro()

RunGitCommand(status --porcelain -unormal)
if(NOT "${LAST_GIT_OUTPUT}" STREQUAL "")
    set(GIT_IS_DIRTY "true")
else()
    set(GIT_IS_DIRTY "false")
endif()

RunGitCommand(show -s "--format=%H" HEAD)
if(NOT "${LAST_GIT_OUTPUT}" STREQUAL "")
    set(GIT_COMMIT_SHA1 "\"${LAST_GIT_OUTPUT}\"")
else()
    set(GIT_COMMIT_SHA1 "\"\"")
endif()

RunGitCommand(describe --long --tags --always HEAD)
if(NOT "${LAST_GIT_OUTPUT}" STREQUAL "")
    set(GIT_DESCRIBE "\"${LAST_GIT_OUTPUT}\"")
else()
    set(GIT_DESCRIBE "\"\"")
endif()

RunGitCommand(show -s "--format=%ci" HEAD)
if(NOT "${LAST_GIT_OUTPUT}" STREQUAL "")
    set(GIT_COMMIT_DATE "\"${LAST_GIT_OUTPUT}\"")
else()
    set(GIT_COMMIT_DATE "\"\"")
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/GitInfo.cpp.in ${CMAKE_CURRENT_BINARY_DIR}/GitInfo.cpp @ONLY)

add_library(GitInfo STATIC GitInfo.cpp)
target_include_directories(GitInfo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(GitInfo PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

include(GenerateExportHeader)
generate_export_header(GitInfo
    EXPORT_MACRO_NAME GITINFO_API
    EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/GitInfo.api.h
)


