cmake_minimum_required(VERSION 3.10)
project(termtest)

set (CMAKE_CXX_STANDARD 20)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(TERMTEST_LINT "Whether or not to enable clang-tidy checks" OFF)
option(TERMTEST_LINT_WARNINGS_ARE_ERRORS "Whether or not to set -warnings-as-errors" OFF)
option(TERMTEST_SANITISE "Whether or not to enable -fsanitize=undefined" OFF)
option(TERMTEST_DOXYGEN "Whether or not to enable doxygen targets" OFF)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(SHARED OFF)

if(TERMTEST_SANITISE)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
endif()

if (TERMTEST_DOXYGEN)

    find_package(Doxygen REQUIRED)
    if (DOXYGEN_FOUND)
        set(DOXYGEN_GENERATE_HTML YES)
        set(DOXYGEN_GENERATE_MAN NO)
        set(DOXYGEN_EXCLUDE_SYMBOLS "std::*")
        set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "README.md")
        set(DOXYGEN_RECURSIVE YES)
        set(DOXYGEN_EXTRACT_STATIC YES)
        set(DOXYGEN_EXTRACT_ALL YES)
        list(
            APPEND DOXYGEN_EXCLUDE_PATTERNS
            "*/build/*"
            "*/_deps/*"
        )

        doxygen_add_docs(
            doxygen
            ${PROJECT_SOURCE_DIR}
            COMMENT "Generate documentation"
        )
    endif()
endif()

include(FetchContent)
FetchContent_Declare(stc
    GIT_REPOSITORY https://github.com/LunarWatcher/stc
)
FetchContent_MakeAvailable(stc)

add_subdirectory(src)
add_subdirectory(tests)

add_custom_target(run
    COMMAND termtest
    DEPENDS termtest
    COMMENT "Run termtest")
add_custom_target(test
    COMMAND tests
    DEPENDS tests
    COMMENT "Test termtest")
# vim:ft=cmake
