include(FetchContent)

FetchContent_Declare(
  RxGSD
  GIT_REPOSITORY https://github.com/ZQF-ReVN/RxGSD.git
  GIT_TAG 98f62fef8f824baaa569320d793080ff0fd54d1a)

FetchContent_MakeAvailable(RxGSD)


add_subdirectory(GSP_Editor)
add_subdirectory(BMZ_Editor)
add_subdirectory(SPT_Cryptor)
add_subdirectory(SPT_Parser)
add_subdirectory(SPT_Text_Editor)