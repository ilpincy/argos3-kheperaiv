#
# kheperaiv headers
#
# argos3/plugins/robots/kheperaiv/control_interface
set(ARGOS3_HEADERS_PLUGINS_ROBOTS_KHEPERAIV_CONTROLINTERFACE
  control_interface/ci_kheperaiv_camera_sensor.h
  control_interface/ci_kheperaiv_encoder_sensor.h
  control_interface/ci_kheperaiv_ground_sensor.h
  control_interface/ci_kheperaiv_lidar_sensor.h
  control_interface/ci_kheperaiv_light_sensor.h
  control_interface/ci_kheperaiv_proximity_sensor.h
  control_interface/ci_kheperaiv_ultrasound_sensor.h)
if(BUZZ_FOUND)
  set(ARGOS3_HEADERS_PLUGINS_ROBOTS_KHEPERAIV_CONTROLINTERFACE
    ${ARGOS3_HEADERS_PLUGINS_ROBOTS_KHEPERAIV_CONTROLINTERFACE}
    control_interface/buzz_controller_kheperaiv.h)
endif(BUZZ_FOUND)
# argos3/plugins/robots/kheperaiv/simulator
if(ARGOS_BUILD_FOR_SIMULATOR)
  set(ARGOS3_HEADERS_PLUGINS_ROBOTS_KHEPERAIV_SIMULATOR
    simulator/dynamics2d_kheperaiv_model.h
    simulator/kheperaiv_entity.h
    simulator/kheperaiv_light_rotzonly_sensor.h
    simulator/kheperaiv_measures.h
    simulator/kheperaiv_ground_rotzonly_sensor.h
    simulator/kheperaiv_lidar_default_sensor.h
    simulator/kheperaiv_proximity_default_sensor.h
    simulator/kheperaiv_ultrasound_default_sensor.h)
endif(ARGOS_BUILD_FOR_SIMULATOR)
# argos3/plugins/robots/kheperaiv/real_robot
if(ARGOS_BUILD_FOR STREQUAL "khiv")
  set(ARGOS3_HEADERS_PLUGINS_ROBOTS_KHEPERAIV_REALROBOT
    real_robot/real_kheperaiv.h
    real_robot/real_kheperaiv_device.h
    real_robot/real_kheperaiv_differential_steering_device.h
    real_robot/real_kheperaiv_differential_steering_actuator.h
    #real_robot/real_kheperaiv_gripper_actuator.h
    real_robot/real_kheperaiv_leds_actuator.h
    real_robot/real_kheperaiv_battery_sensor.h
    real_robot/real_kheperaiv_camera_sensor.h
    real_robot/real_kheperaiv_encoder_sensor.h
    real_robot/real_kheperaiv_ground_sensor.h
    real_robot/real_kheperaiv_lidar_sensor.h
    real_robot/real_kheperaiv_proximity_sensor.h
    real_robot/real_kheperaiv_ultrasound_sensor.h)
endif(ARGOS_BUILD_FOR STREQUAL "khiv")

#
# kheperaiv sources
#
set(ARGOS3_SOURCES_PLUGINS_ROBOTS_KHEPERAIV
  ${ARGOS3_HEADERS_PLUGINS_ROBOTS_KHEPERAIV_CONTROLINTERFACE}
  control_interface/ci_kheperaiv_camera_sensor.cpp
  control_interface/ci_kheperaiv_encoder_sensor.cpp
  control_interface/ci_kheperaiv_ground_sensor.cpp
  control_interface/ci_kheperaiv_lidar_sensor.cpp
  control_interface/ci_kheperaiv_light_sensor.cpp
  control_interface/ci_kheperaiv_proximity_sensor.cpp
  control_interface/ci_kheperaiv_ultrasound_sensor.cpp)
if(BUZZ_FOUND)
  set(ARGOS3_SOURCES_PLUGINS_ROBOTS_KHEPERAIV
    ${ARGOS3_SOURCES_PLUGINS_ROBOTS_KHEPERAIV}
    control_interface/buzz_controller_kheperaiv.cpp)
endif(BUZZ_FOUND)

if(ARGOS_BUILD_FOR_SIMULATOR)
  set(ARGOS3_SOURCES_PLUGINS_ROBOTS_KHEPERAIV
    ${ARGOS3_SOURCES_PLUGINS_ROBOTS_KHEPERAIV}
    ${ARGOS3_HEADERS_PLUGINS_ROBOTS_KHEPERAIV_SIMULATOR}
    simulator/dynamics2d_kheperaiv_model.cpp
    simulator/kheperaiv_entity.cpp
    simulator/kheperaiv_light_rotzonly_sensor.cpp
    simulator/kheperaiv_measures.cpp
    simulator/kheperaiv_ground_rotzonly_sensor.cpp
    simulator/kheperaiv_lidar_default_sensor.cpp
    simulator/kheperaiv_proximity_default_sensor.cpp
    simulator/kheperaiv_ultrasound_default_sensor.cpp)
  # Compile the graphical visualization only if the necessary libraries have been found
  if(ARGOS_QTOPENGL_FOUND)
    include_directories(${ARGOS_QTOPENGL_INCLUDE_DIRS})
    set(ARGOS3_HEADERS_PLUGINS_ROBOTS_KHEPERAIV_SIMULATOR
      ${ARGOS3_HEADERS_PLUGINS_ROBOTS_KHEPERAIV_SIMULATOR}
      simulator/qtopengl_kheperaiv.h)
    set(ARGOS3_SOURCES_PLUGINS_ROBOTS_KHEPERAIV
      ${ARGOS3_SOURCES_PLUGINS_ROBOTS_KHEPERAIV}
      simulator/qtopengl_kheperaiv.h
      simulator/qtopengl_kheperaiv.cpp)
  endif(ARGOS_QTOPENGL_FOUND)
endif(ARGOS_BUILD_FOR_SIMULATOR)
if(ARGOS_BUILD_FOR STREQUAL "khiv")
  set(ARGOS3_SOURCES_PLUGINS_ROBOTS_KHEPERAIV
    ${ARGOS3_SOURCES_PLUGINS_ROBOTS_KHEPERAIV}
    ${ARGOS3_HEADERS_PLUGINS_ROBOTS_KHEPERAIV_REALROBOT}
    real_robot/real_kheperaiv.cpp
    real_robot/real_kheperaiv_device.cpp
    real_robot/real_kheperaiv_differential_steering_device.cpp
    real_robot/real_kheperaiv_differential_steering_actuator.cpp
    #real_robot/real_kheperaiv_gripper_actuator.cpp
    real_robot/real_kheperaiv_leds_actuator.cpp
    real_robot/real_kheperaiv_battery_sensor.cpp
    real_robot/real_kheperaiv_camera_sensor.cpp
    real_robot/real_kheperaiv_encoder_sensor.cpp
    real_robot/real_kheperaiv_ground_sensor.cpp
    real_robot/real_kheperaiv_lidar_sensor.cpp
    real_robot/real_kheperaiv_proximity_sensor.cpp
    real_robot/real_kheperaiv_ultrasound_sensor.cpp)
endif(ARGOS_BUILD_FOR STREQUAL "khiv")

#
# Create kheperaiv plugin
#
add_library(argos3plugin_${ARGOS_BUILD_FOR}_kheperaiv SHARED ${ARGOS3_SOURCES_PLUGINS_ROBOTS_KHEPERAIV})
target_link_libraries(argos3plugin_${ARGOS_BUILD_FOR}_kheperaiv
  argos3plugin_${ARGOS_BUILD_FOR}_genericrobot)
if(ARGOS_BUILD_FOR_SIMULATOR)
  target_link_libraries(argos3plugin_${ARGOS_BUILD_FOR}_kheperaiv
    argos3plugin_${ARGOS_BUILD_FOR}_dynamics2d)
  if(ARGOS_QTOPENGL_FOUND)
    target_link_libraries(argos3plugin_${ARGOS_BUILD_FOR}_kheperaiv argos3plugin_${ARGOS_BUILD_FOR}_qtopengl)
  endif(ARGOS_QTOPENGL_FOUND)
else(ARGOS_BUILD_FOR_SIMULATOR)
  target_link_libraries(argos3plugin_${ARGOS_BUILD_FOR}_kheperaiv
    -lkhepera)
endif(ARGOS_BUILD_FOR_SIMULATOR)
if(BUZZ_FOUND)
  target_link_libraries(argos3plugin_${ARGOS_BUILD_FOR}_kheperaiv argos3plugin_${ARGOS_BUILD_FOR}_buzz ${BUZZ_LIBRARY})
endif(BUZZ_FOUND)

#
# Create battery monitor
#
if(ARGOS_BUILD_FOR STREQUAL "khiv")
  add_executable(battery real_robot/battery.c)
  target_link_libraries(battery -lkhepera)
endif(ARGOS_BUILD_FOR STREQUAL "khiv")

#
# Installation
#
install(FILES ${ARGOS3_HEADERS_PLUGINS_ROBOTS_KHEPERAIV_CONTROLINTERFACE} DESTINATION include/argos3/plugins/robots/kheperaiv/control_interface)

if(ARGOS_BUILD_FOR_SIMULATOR)
  install(FILES ${ARGOS3_HEADERS_PLUGINS_ROBOTS_KHEPERAIV_SIMULATOR} DESTINATION include/argos3/plugins/robots/kheperaiv/simulator)
  install(FILES simulator/kheperaiv_texture_bottom.png simulator/kheperaiv_texture_side.png simulator/kheperaiv_texture_top.png DESTINATION include/argos3/plugins/simulator/visualizations/qt-opengl/textures)
else(ARGOS_BUILD_FOR_SIMULATOR)
  install(FILES ${ARGOS3_HEADERS_PLUGINS_ROBOTS_KHEPERAIV_REALROBOT} DESTINATION include/argos3/plugins/robots/kheperaiv/real_robot)
  install(FILES real_robot/main.cpp DESTINATION include/argos3/plugins/robots/kheperaiv/real_robot)
endif(ARGOS_BUILD_FOR_SIMULATOR)

install(TARGETS argos3plugin_${ARGOS_BUILD_FOR}_kheperaiv
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib/argos3
  ARCHIVE DESTINATION lib/argos3)
