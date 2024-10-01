include(FetchContent)

FetchContent_Declare(
  RxValkyria
  GIT_REPOSITORY https://github.com/ZQF-ReVN/RxValkyria.git
  GIT_TAG 06d365e21f7e2e4ba929ac7925051aeb743aa056)

FetchContent_MakeAvailable(RxValkyria)


add_subdirectory(DAT_Editor)
add_subdirectory(SDT_Signer)
add_subdirectory(SDT_TextEditor)
# add_subdirectory(VFS_Hook)
