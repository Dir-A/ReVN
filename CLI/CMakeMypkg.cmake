include(FetchContent)

FetchContent_Declare(
  ZxFile
  GIT_REPOSITORY https://github.com/ZQF-Zut/ZxFile.git
  GIT_TAG 6ed88873eca2ac9a533ca0322eb363a94f551d2e)

FetchContent_MakeAvailable(ZxFile)

FetchContent_Declare(
  ZxMem
  GIT_REPOSITORY https://github.com/ZQF-Zut/ZxMem.git
  GIT_TAG bd607ae77e978e72cea44fe8c497aedfd266ff7d)

FetchContent_MakeAvailable(ZxMem)

FetchContent_Declare(
  ZxCvt
  GIT_REPOSITORY https://github.com/ZQF-Zut/ZxCvt.git
  GIT_TAG 4e6ddaab9b88d1ea848b7b1cbab0d46462b6ccff)

FetchContent_MakeAvailable(ZxCvt)

FetchContent_Declare(
  ZxJson
  GIT_REPOSITORY https://github.com/ZQF-Zut/ZxJson.git
  GIT_TAG 5eaa04d284b49d3e950effde6b059c3928ad7719)

FetchContent_MakeAvailable(ZxJson)

FetchContent_Declare(
  ZxFS
  GIT_REPOSITORY https://github.com/ZQF-Zut/ZxFS.git
  GIT_TAG 9c04dbdc471f748ea95e15967bd34cd0bbcf7ddb)

FetchContent_MakeAvailable(ZxFS)


FetchContent_Declare(
  ZxArg
  GIT_REPOSITORY https://github.com/ZQF-Zut/ZxArg.git
  GIT_TAG 425e1a535b8fc99e7e97dcc4c1c561fc1d134e54)

FetchContent_MakeAvailable(ZxArg)

if((CMAKE_SYSTEM_NAME STREQUAL "Windows") AND MSVC)
    FetchContent_Declare(
        ZxHook
        GIT_REPOSITORY https://github.com/ZQF-Zut/ZxHook.git
        GIT_TAG f2bdbc8c4b33fc31dd53fcb78f2d2ac7778e2854)

    FetchContent_MakeAvailable(ZxHook)
endif()


if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(ZLIB_BUILD_EXAMPLES OFF)
    FetchContent_Declare(
        zlib
        GIT_REPOSITORY https://github.com/madler/zlib.git
        GIT_TAG v1.3.1)

    FetchContent_MakeAvailable(zlib)

    if(BUILD_SHARED_LIBS)
        add_library(ZLIB::ZLIB ALIAS zlib)
    else()
        add_library(ZLIB::ZLIB ALIAS zlibstatic)
    endif()
    
elseif(UNIX)
    find_package(ZLIB REQUIRED)
endif()