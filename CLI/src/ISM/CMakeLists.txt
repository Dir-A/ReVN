include(FetchContent)

FetchContent_Declare(
  RxISM
  GIT_REPOSITORY https://github.com/ZQF-ReVN/RxISM.git
  GIT_TAG f8bb4c37a37d24b980dce011dc8d55d997f96b0a)

FetchContent_MakeAvailable(RxISM)


add_subdirectory("ISA_Editor")
