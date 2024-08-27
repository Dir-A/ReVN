include(FetchContent)

FetchContent_Declare(
  ZxFile
  GIT_REPOSITORY https://github.com/ZQF-Zut/ZxFile.git
  GIT_TAG 662f47476960f82fa02cf66eb5b9410885903c55)

FetchContent_MakeAvailable(ZxFile)

FetchContent_Declare(
  ZxMem
  GIT_REPOSITORY https://github.com/ZQF-Zut/ZxMem.git
  GIT_TAG 2c66243e752c7ff8a3d84cb52fec8a69eb21949b)

FetchContent_MakeAvailable(ZxMem)

FetchContent_Declare(
  ZxCvt
  GIT_REPOSITORY https://github.com/ZQF-Zut/ZxCvt.git
  GIT_TAG 3c82f10f0913cb5810123c2a52ab7197a103cb4f)

FetchContent_MakeAvailable(ZxCvt)

FetchContent_Declare(
  ZxJson
  GIT_REPOSITORY https://github.com/ZQF-Zut/ZxJson.git
  GIT_TAG 02afdb1461aa5cbde392302f484d89efaab95b64)

FetchContent_MakeAvailable(ZxJson)

FetchContent_Declare(
  ZxFS
  GIT_REPOSITORY https://github.com/ZQF-Zut/ZxFS.git
  GIT_TAG 036919fc0e55667958d553393940f4e6477bbf99)

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


