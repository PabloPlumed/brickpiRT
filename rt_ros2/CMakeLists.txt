cmake_minimum_required(VERSION 3.16)
project(rt_ros2 LANGUAGES CXX)

if(CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
  add_compile_options(-Wall -Wextra)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)

# FIND DEPENDENCIES
set(THIS_PACKAGE_INCLUDE_DEPENDS
  rclcpp
  sensor_msgs
  geometry_msgs
  std_msgs
)

# VENDOR (para cactus-rt)
add_subdirectory(vendor)

# --- EJECUTABLES ---

# 1. Ejecutable original
add_executable(rt_ros2
  src/main.cc
  src/nodo_actuador.cpp
  src/nodo_maquina_estados.cpp
)

# 2. Ejecutable para experimentos de Tiempo Real (RT)
add_executable(main_rt
  src/mainRT.cc
  src/nodo_actuador.cpp
  src/nodo_maquina_estados.cpp
)

# 3. Ejecutable para experimentos Normales (Best-Effort)
add_executable(main_be
  src/mainBE.cc
  src/nodo_actuador.cpp
  src/nodo_maquina_estados.cpp
)

# Configuración de los ejecutables
foreach(exe rt_ros2 main_rt main_be)
  target_include_directories(${exe} PRIVATE include)
  target_compile_features(${exe} PRIVATE cxx_std_17)
  ament_target_dependencies(${exe} ${THIS_PACKAGE_INCLUDE_DEPENDS})
  target_link_libraries(${exe} cactus_rt)
endforeach()

# --- INSTALACIÓN ---

# Instalar los binarios
install(TARGETS 
  rt_ros2
  main_rt
  main_be
  DESTINATION lib/${PROJECT_NAME}
)

# Instalar la carpeta launch (Imprescindible para ros2 launch)
install(DIRECTORY launch/
  DESTINATION share/${PROJECT_NAME}
)

# --- TESTS ---
option(BUILD_TESTS "Compilar tests" ON)
if(BUILD_TESTS)
  add_executable(nodo_test test/nodo_test.cpp)
  target_include_directories(nodo_test PRIVATE include)
  target_compile_features(nodo_test PRIVATE cxx_std_17)
  ament_target_dependencies(nodo_test ${THIS_PACKAGE_INCLUDE_DEPENDS})
  install(TARGETS nodo_test DESTINATION lib/${PROJECT_NAME})
endif()

ament_package()
