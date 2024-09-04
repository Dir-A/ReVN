include(FetchContent)

FetchContent_Declare(
  RxPJADV
  GIT_REPOSITORY https://github.com/ZQF-ReVN/RxPJADV.git
  GIT_TAG c15fdf3a56d0e99834dbe0f7f28cd9ab6bd3a86b)

FetchContent_MakeAvailable(RxPJADV)


add_subdirectory(Pack_V2_Editor)
add_subdirectory(Text_Editor)
add_subdirectory(TextDataDat_Cryptor)