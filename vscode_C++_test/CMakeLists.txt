cmake_minimum_required(VERSION 2.8.3)
project(test1)
# 使用ros自带的opecv
set(OpenCV_DIR /opt/ros/kinetic/share/OpenCV-3.3.1-dev)
find_package(catkin REQUIRED COMPONENTS 
  roscpp
  OpenCV
)

include_directories(
 include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

add_executable(testing src/test.cpp)
target_link_libraries(testing
${catkin_LIBRARIES} 
${OpenCV_LIBRARIES}
)

