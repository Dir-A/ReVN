# OutPath
if (CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/.bin/x32-${CMAKE_BUILD_TYPE}/")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/.bin/x32-${CMAKE_BUILD_TYPE}/")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/.bin/x32-${CMAKE_BUILD_TYPE}/lib/")
else()
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/.bin/x64-${CMAKE_BUILD_TYPE}/")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/.bin/x64-${CMAKE_BUILD_TYPE}/")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/.bin/x64-${CMAKE_BUILD_TYPE}/lib/")
endif()

# Link
if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    # LTCG
    cmake_policy(SET CMP0069 NEW) 
    set(CMAKE_POLICY_DEFAULT_CMP0069 NEW)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT IPO_CHECK_RESULT OUTPUT output)
    if(IPO_CHECK_RESULT)
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
    else()
        message(WARNING "IPO is not supported: ${output}")
    endif()

    # Static Library
    set(BUILD_SHARED_LIBS OFF)

    # Static Runtime
    if(MSVC)
        set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreaded)
    else()
        SET(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
        add_compile_options(-ffunction-sections)
        add_compile_options(-fdata-sections)
        add_link_options(-static)
        add_link_options(-Wl,--gc-sections)
        if(NOT CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
            add_link_options(-s)
        endif()
    endif()
else()
    # set(BUILD_SHARED_LIBS ON)
endif()

# Compiler
if(MSVC)
    if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(/Gy)
        add_compile_options(/Zc:inline)
    endif()
endif()
