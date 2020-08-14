cmake_minimum_required(VERSION 3.5)
project(hello_world)

set(CMAKE_CXX_STANDARD 14)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(std_msgs REQUIRED)

# ビルド設定の便利関数
function(custom_executable target)
  add_executable(${target} src/${target}.cpp)
  ament_target_dependencies(${target}
    "rclcpp"
    "std_msgs")
  install(TARGETS ${target}
    DESTINATION lib/${PROJECT_NAME})
endfunction()

# talkerノードのビルド設定
custom_executable(talker)
# listenerノードのビルド設定
custom_executable(listener)
custom_executable(talker_listener)

ament_package()
