include(FetchContent)

FetchContent_Declare(
  RxGSD
  GIT_REPOSITORY https://github.com/ZQF-ReVN/RxGSD.git
  GIT_TAG eb41a7b1082795415609ee0944307e20e9645dd8)

FetchContent_MakeAvailable(RxGSD)


add_subdirectory(GSP_Editor)
add_subdirectory(BMZ_Editor)
add_subdirectory(SPT_Cryptor)
add_subdirectory(SPT_Parser)
add_subdirectory(SPT_Text_Editor)