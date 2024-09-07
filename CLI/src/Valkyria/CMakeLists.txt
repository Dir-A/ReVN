include(FetchContent)

FetchContent_Declare(
  RxValkyria
  GIT_REPOSITORY https://github.com/ZQF-ReVN/RxValkyria.git
  GIT_TAG 6b8da6d42e19fe408c578f02c7247fd05d24092a)

FetchContent_MakeAvailable(RxValkyria)


add_subdirectory(DAT_Editor)
add_subdirectory(SDT_Signer)
add_subdirectory(SDT_TextEditor)
# add_subdirectory(VFS_Hook)