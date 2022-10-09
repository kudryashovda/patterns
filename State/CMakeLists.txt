set(project "my_prog")
project(my_prog)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable (${PROJECT_NAME} main.cpp state.h state.cpp)