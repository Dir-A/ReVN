include(FetchContent)

FetchContent_Declare(
  RxPJADV
  GIT_REPOSITORY https://github.com/ZQF-ReVN/RxPJADV.git
  GIT_TAG 298092fff155309f909c952a4d5be872e91b8b88)

FetchContent_MakeAvailable(RxPJADV)


add_subdirectory(Pack_V2_Editor)
add_subdirectory(Text_Editor)
add_subdirectory(TextDataDat_Cryptor)
