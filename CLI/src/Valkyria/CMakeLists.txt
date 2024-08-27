include(FetchContent)

FetchContent_Declare(
  RxValkyria
  GIT_REPOSITORY https://github.com/ZQF-ReVN/RxValkyria.git
  GIT_TAG 782611556da98637d785d4e5912bcda0256d55ea)

FetchContent_MakeAvailable(RxValkyria)


add_subdirectory(DAT_Editor)
add_subdirectory(SDT_Signer)
add_subdirectory(SDT_TextEditor)
# add_subdirectory(VFS_Hook)