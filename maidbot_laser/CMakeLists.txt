cmake_minimum_required(VERSION 2.8.3)
project(maidbot_laser)
add_definitions(-std=c++11)



# find_package(catkin REQUIRED)


find_package(catkin REQUIRED COMPONENTS
  message_generation
  roscpp
  tf
)

add_message_files(FILES
  Position.msg
)


generate_messages(DEPENDENCIES
  std_msgs
)


catkin_package(
  CATKIN_DEPENDS
  message_runtime
)


include_directories(include)

add_executable(laser_node src/laser_node.cpp)


add_dependencies(laser_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(laser_node
  ${catkin_LIBRARIES}
)

add_executable(send_pose
  src/send_pose.cpp
)
add_dependencies(send_pose ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(send_pose
  ${catkin_LIBRARIES}
)