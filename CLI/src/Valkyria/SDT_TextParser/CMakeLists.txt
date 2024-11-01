# Project Name
project(Valkyria_SDT_TextParser)

# Current Project
add_executable("${PROJECT_NAME}" "main.cpp")
target_compile_features("${PROJECT_NAME}" PRIVATE cxx_std_23)
target_compile_options("${PROJECT_NAME}" PRIVATE "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# Add Library
target_link_libraries("${PROJECT_NAME}" PRIVATE ReVN::RxValkyria::Core Zut::ZxArg Zut::ZxFS)

# Warning
if(MSVC)
    target_compile_options("${PROJECT_NAME}" PRIVATE /W4)
else()
    target_compile_options("${PROJECT_NAME}" PRIVATE -Wall -Wextra)
endif()
