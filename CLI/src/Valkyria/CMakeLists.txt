include(FetchContent)

FetchContent_Declare(
  RxValkyria
  GIT_REPOSITORY https://github.com/ZQF-ReVN/RxValkyria.git
  GIT_TAG 9edcabaffb06e0da3b7b30154da63afb9e425ca4)

FetchContent_MakeAvailable(RxValkyria)


add_subdirectory(DAT_Editor)
add_subdirectory(SDT_Signer)
add_subdirectory(SDT_TextEditor)
# add_subdirectory(VFS_Hook)
