include(FetchContent)

FetchContent_Declare(
  RxGSD
  GIT_REPOSITORY https://github.com/ZQF-ReVN/RxGSD.git
  GIT_TAG 8001930045d72cf3a8b79db370daf071ee39cde3)

FetchContent_MakeAvailable(RxGSD)


add_subdirectory(GSP_Editor)
add_subdirectory(BMZ_Editor)
add_subdirectory(SPT_Cryptor)
add_subdirectory(SPT_Parser)
add_subdirectory(SPT_Text_Editor)
