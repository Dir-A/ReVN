include(FetchContent)

FetchContent_Declare(
  RxGSD
  GIT_REPOSITORY https://github.com/ZQF-ReVN/RxGSD.git
  GIT_TAG dcefb1c4237fa048f1fb0e19cca15a5997580e6e)

FetchContent_MakeAvailable(RxGSD)


add_subdirectory(GSP_Editor)
add_subdirectory(BMZ_Editor)
add_subdirectory(SPT_Cryptor)
add_subdirectory(SPT_Parser)
add_subdirectory(SPT_Text_Editor)
