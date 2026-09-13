cmake_minimum_required(VERSION 3.20)
project(tddd38Labbar CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENTIONS OFF)

# säger att den ska bygga degub som standrar, om ingent annat sägs
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "välj byggtyp!" FORCE)
endif()

# denna tvingar compile_command.json till initellisece eller lsp
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "" FORCE)

if (CMAKE_EXPORT_COMPILE_COMMANDS)
    set(SRC_FILE "$CMAKE_BINARY_DIR}/compile_command.json")
    set(DST_FILE "$CMAKE_SOURCE_DIR}/compile_command.json")
    execute_process(
      COMMAND $CMAKE_COMMAND} -E create_symLink $SRC_FILE} ${DST_FILE}
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endif()

include_directories(src)
# file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp" "tester/*.cpp")

add_executable(reduce "./reduce.cpp")
add_executable(factorial "./factorial.cpp")

include(FetchContent)

# Definiera var Catch2 ska laddas ner ifrån
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.5.2
)

# Gör Catch2 tillgängligt
# FetchContent_MakeAvailable(Catch2)
# Skapa BARA en körbar fil för testprogram
# add_executable(test_labb2 "tester/test_tdde18_labb2.cpp")
# add_executable(test_labb3 "tester/test_tdde18_labb3.cpp")
# add_executable(test_vector "tester/test_tddd38_vector.cpp" "src/TDDD38_mathematical_vector/vector2D.cpp")
# add_executable(test_queue "tester/test_tddd38_queue.cpp")

# Länka in Catch2
# target_link_libraries(test_labb2 PRIVATE Catch2::Catch2WithMain)
# target_link_libraries(test_labb3 PRIVATE Catch2::Catch2WithMain)
# target_link_libraries(test_vector PRIVATE Catch2::Catch2WithMain)
# target_link_libraries(test_queue PRIVATE Catch2::Catch2WithMain)
