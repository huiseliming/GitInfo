
set(PRE_CONFIGURE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/GitInfo.cpp.in")
set(POST_CONFIGURE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/GitInfo.cpp")
include(git_watcher.cmake)

add_library(GitInfo STATIC ${POST_CONFIGURE_FILE})
target_include_directories(GitInfo SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_dependencies(GitInfo check_git)
