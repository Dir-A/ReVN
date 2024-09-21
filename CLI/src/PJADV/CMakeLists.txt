include(FetchContent)

FetchContent_Declare(
  RxPJADV
  GIT_REPOSITORY https://github.com/ZQF-ReVN/RxPJADV.git
  GIT_TAG 9fd2f5dd1ea78d7273cdce9587d1b9b345d7aad9)

FetchContent_MakeAvailable(RxPJADV)


add_subdirectory(Pack_V2_Editor)
add_subdirectory(Text_Editor)
add_subdirectory(TextDataDat_Cryptor)
