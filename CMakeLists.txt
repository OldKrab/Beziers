cmake_minimum_required(VERSION 3.14)

project(beziers)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.5.1)
FetchContent_MakeAvailable(SFML)

file(GLOB SRC
     "src/**/*.cpp"
     "src/*.cpp"
)
message("BOOBA " ${SRC} " \n\n\n\n\n") 
add_executable(beziers ${SRC})
target_include_directories(beziers PRIVATE src)
target_link_libraries(beziers PRIVATE sfml-graphics)
target_compile_features(beziers PRIVATE cxx_std_20)
find_package(TBB REQUIRED)
target_link_libraries(beziers PRIVATE TBB::tbb)