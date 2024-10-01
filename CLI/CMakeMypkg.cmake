include(FetchContent)

FetchContent_Declare(
  ZxFile
  GIT_REPOSITORY https://github.com/ZQF-Zut/ZxFile.git
  GIT_TAG fe4912736343c69bedd77b4ca0c10e9e4b962bec)

FetchContent_MakeAvailable(ZxFile)

FetchContent_Declare(
  ZxMem
  GIT_REPOSITORY https://github.com/ZQF-Zut/ZxMem.git
  GIT_TAG 873edf0a29e0c54c1003d3544a02010769cea7b8)

FetchContent_MakeAvailable(ZxMem)

FetchContent_Declare(
  ZxCvt
  GIT_REPOSITORY https://github.com/ZQF-Zut/ZxCvt.git
  GIT_TAG cd5d3967a1c7552fdd054215a2961e3cb43d1312)

FetchContent_MakeAvailable(ZxCvt)

FetchContent_Declare(
  ZxJson
  GIT_REPOSITORY https://github.com/ZQF-Zut/ZxJson.git
  GIT_TAG f7f8a51a9d323dbaa36f5e20583b17849f877d38)

FetchContent_MakeAvailable(ZxJson)

FetchContent_Declare(
  ZxFS
  GIT_REPOSITORY https://github.com/ZQF-Zut/ZxFS.git
  GIT_TAG f7c3d1082b050d203246ca259ea07893c5033494)

FetchContent_MakeAvailable(ZxFS)

FetchContent_Declare(
  ZxArg
  GIT_REPOSITORY https://github.com/ZQF-Zut/ZxArg.git
  GIT_TAG d3708ef3c818313974983daf4d1648bd1767c0bf)

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
