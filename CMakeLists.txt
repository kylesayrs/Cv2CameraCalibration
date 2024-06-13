# set up project
cmake_minimum_required(VERSION 3.25.2)
project(Cv2CameraCalibration)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include libraries
find_package(OpenCV REQUIRED)

# create executable
add_executable(
    ccc
    src/main.cpp
)

# link libraries
target_link_libraries(
    ccc
    ${OpenCV_LIBS}
)


# includes
include_directories(
    ccc
    ${OpenCV_INCLUDE_DIRS}
    PUBLIC
        include
)