cmake_minimum_required(VERSION 3.10)
project(spendtrack)

# Print CMake version and paths for context
message(STATUS "CMake Version: ${CMAKE_VERSION}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")

# Manually specify SQLite3 paths
set(SQLITE3_INCLUDE_DIR "/usr/include")
set(SQLITE3_LIBRARY "/usr/lib/x86_64-linux-gnu/libsqlite3.so")

# Verify SQLite3 files exist
if(NOT EXISTS "${SQLITE3_INCLUDE_DIR}/sqlite3.h")
  message(FATAL_ERROR "SQLite3 header not found at ${SQLITE3_INCLUDE_DIR}/sqlite3.h. Please install libsqlite3-dev or adjust SQLITE3_INCLUDE_DIR.")
endif()
if(NOT EXISTS "${SQLITE3_LIBRARY}")
  message(FATAL_ERROR "SQLite3 library not found at ${SQLITE3_LIBRARY}. Please install libsqlite3-dev or adjust SQLITE3_LIBRARY.")
endif()

# Create SQLite3::SQLite3 target
add_library(SQLite3::SQLite3 INTERFACE IMPORTED)
set_target_properties(SQLite3::SQLite3 PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${SQLITE3_INCLUDE_DIR}"
  INTERFACE_LINK_LIBRARIES "${SQLITE3_LIBRARY}"
)

# Print SQLite3 configuration for confirmation
message(STATUS "SQLite3_INCLUDE_DIR: ${SQLITE3_INCLUDE_DIR}")
message(STATUS "SQLite3_LIBRARY: ${SQLITE3_LIBRARY}")
get_cmake_property(_targets IMPORTED_TARGETS)
message(STATUS "Imported Targets: ${_targets}")
if(TARGET SQLite3::SQLite3)
  message(STATUS "SQLite3::SQLite3 target exists")
else()
  message(FATAL_ERROR "Failed to create SQLite3::SQLite3 target")
endif()

# Rest of your CMakeLists.txt
include(CTest)
add_library(spendtracklib STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/spendtrack.c)
target_include_directories(spendtracklib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(spendtracklib PUBLIC SQLite3::SQLite3)
add_executable(spendtrack ${CMAKE_CURRENT_SOURCE_DIR}/src/spendtrack.c)
target_link_libraries(spendtrack spendtracklib SQLite3::SQLite3)
target_compile_definitions(spendtrack PRIVATE IS_EXE)
add_library(Unity STATIC external/src/unity.c)
target_include_directories(Unity PUBLIC external/unity/src)
add_executable(spendtracktest test/test_spendtrack.c)
target_link_libraries(spendtracktest spendtracklib Unity SQLite3::SQLite3)
add_test(NAME spendtracktest COMMAND spendtracktest)
