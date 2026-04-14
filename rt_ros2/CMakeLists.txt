cmake_minimum_required(VERSION 3.16)
project(rt_ros2 LANGUAGES CXX)

if(CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
  add_compile_options(-Wall -Wextra)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
#find_package(ev3_sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)

# FIND DEPENDENCIES
set(THIS_PACKAGE_INCLUDE_DEPENDS
  rclcpp
# descomentar esto si se quieren utilizar valores discretos de color,tmb siguiente funcion y package.xml
# ev3_sensor_msgs
  sensor_msgs
  geometry_msgs
  std_msgs
)

# VENDOR (para cactus-rt)
add_subdirectory(vendor)

# COMPILE
add_executable(rt_ros2
  src/main.cc
  src/nodo_actuador.cpp
  src/nodo_maquina_estados.cpp
)

target_include_directories(rt_ros2 PRIVATE include)
target_compile_features(rt_ros2 PRIVATE cxx_std_17)
ament_target_dependencies(rt_ros2 ${THIS_PACKAGE_INCLUDE_DEPENDS})

target_link_libraries(rt_ros2
  cactus_rt
)

# INSTALL
install(TARGETS rt_ros2
  DESTINATION lib/${PROJECT_NAME}
)

# PARA TESTS
option(BUILD_TESTS "Compilar tests" ON)

if(BUILD_TESTS)
  add_executable(nodo_test test/nodo_test.cpp)
  target_include_directories(nodo_test PRIVATE include)
  target_compile_features(nodo_test PRIVATE cxx_std_17)
  ament_target_dependencies(nodo_test ${THIS_PACKAGE_INCLUDE_DEPENDS})
  install(TARGETS nodo_test DESTINATION lib/${PROJECT_NAME})
endif()
