include(FetchContent)

FetchContent_Declare(
  RxPJADV
  GIT_REPOSITORY https://github.com/ZQF-ReVN/RxPJADV.git
  GIT_TAG 8f2159b97301b294e9fbd1136ecb7db25c8a11cc)

FetchContent_MakeAvailable(RxPJADV)


add_subdirectory(Pack_V2_Editor)
add_subdirectory(Text_Editor)
add_subdirectory(TextDataDat_Cryptor)