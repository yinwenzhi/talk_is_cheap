cmake_minimum_required(VERSION 2.8.3)
project(test)

# 使用ros自带的opecv
set(OpenCV_DIR /opt/ros/kinetic/share/OpenCV-3.3.1-dev)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  OpenCV
)


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES test
#  CATKIN_DEPENDS roscpp
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

## Declare a C++ library
# add_library(${PROJECT_NAME}
#   src/${PROJECT_NAME}/test.cpp
# )

## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
# add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
add_executable(testing  src/test.cpp)

target_link_libraries(testing   ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
