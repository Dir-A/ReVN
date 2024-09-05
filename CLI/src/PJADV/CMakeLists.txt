include(FetchContent)

FetchContent_Declare(
  RxPJADV
  GIT_REPOSITORY https://github.com/ZQF-ReVN/RxPJADV.git
  GIT_TAG 2b1c3c2e30c8f431aa6a1f885124af9acc4f47a3)

FetchContent_MakeAvailable(RxPJADV)


add_subdirectory(Pack_V2_Editor)
add_subdirectory(Text_Editor)
add_subdirectory(TextDataDat_Cryptor)