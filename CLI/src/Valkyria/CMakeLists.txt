include(FetchContent)

FetchContent_Declare(
  RxValkyria
  GIT_REPOSITORY https://github.com/ZQF-ReVN/RxValkyria.git
  GIT_TAG 55cf9abb958e157e02817bd32cea61c0611619b6)

FetchContent_MakeAvailable(RxValkyria)


add_subdirectory(DAT_Editor)
add_subdirectory(SDT_Signer)
add_subdirectory(SDT_TextParser)
add_subdirectory(SDT_TextEditor)
# add_subdirectory(VFS_Hook)
