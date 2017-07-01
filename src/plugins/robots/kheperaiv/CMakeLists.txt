#
# kheperaiv headers
#
# argos3/plugins/robots/kheperaiv/control_interface
set(ARGOS3_HEADERS_PLUGINS_ROBOTS_KHEPERAIV_CONTROLINTERFACE
  control_interface/ci_kheperaiv_encoder_sensor.h
  control_interface/ci_kheperaiv_ground_sensor.h
  control_interface/ci_kheperaiv_light_sensor.h
  control_interface/ci_kheperaiv_proximity_sensor.h)
# argos3/plugins/robots/kheperaiv/simulator
if(ARGOS_BUILD_FOR_SIMULATOR)
  set(ARGOS3_HEADERS_PLUGINS_ROBOTS_KHEPERAIV_SIMULATOR
    simulator/dynamics2d_kheperaiv_model.h
    simulator/kheperaiv_entity.h
    simulator/kheperaiv_light_rotzonly_sensor.h
    simulator/kheperaiv_measures.h
    simulator/kheperaiv_ground_rotzonly_sensor.h
    simulator/kheperaiv_proximity_default_sensor.h
    simulator/qtopengl_kheperaiv.h)
endif(ARGOS_BUILD_FOR_SIMULATOR)

#
# kheperaiv sources
#
set(ARGOS3_SOURCES_PLUGINS_ROBOTS_KHEPERAIV
  ${ARGOS3_HEADERS_PLUGINS_ROBOTS_KHEPERAIV_CONTROLINTERFACE}
  control_interface/ci_kheperaiv_encoder_sensor.cpp
  control_interface/ci_kheperaiv_ground_sensor.cpp
  control_interface/ci_kheperaiv_light_sensor.cpp
  control_interface/ci_kheperaiv_proximity_sensor.cpp)

if(ARGOS_BUILD_FOR_SIMULATOR)
  set(ARGOS3_SOURCES_PLUGINS_ROBOTS_KHEPERAIV
    ${ARGOS3_SOURCES_PLUGINS_ROBOTS_KHEPERAIV}
    ${ARGOS3_HEADERS_PLUGINS_ROBOTS_KHEPERAIV_SIMULATOR}
    simulator/dynamics2d_kheperaiv_model.cpp
    simulator/kheperaiv_entity.cpp
    simulator/kheperaiv_light_rotzonly_sensor.cpp
    simulator/kheperaiv_measures.cpp
    simulator/kheperaiv_ground_rotzonly_sensor.cpp
    simulator/kheperaiv_proximity_default_sensor.cpp
    simulator/qtopengl_kheperaiv.cpp)
  # Compile the graphical visualization only if the necessary libraries have been found
  include(ARGoSCheckQTOpenGL)
  if(ARGOS_COMPILE_QTOPENGL)
    set(ARGOS3_HEADERS_PLUGINS_ROBOTS_KHEPERAIV_SIMULATOR
      ${ARGOS3_HEADERS_PLUGINS_ROBOTS_KHEPERAIV_SIMULATOR}
      simulator/qtopengl_kheperaiv.h)
    set(ARGOS3_SOURCES_PLUGINS_ROBOTS_KHEPERAIV
      ${ARGOS3_SOURCES_PLUGINS_ROBOTS_KHEPERAIV}
      simulator/qtopengl_kheperaiv.h
      simulator/qtopengl_kheperaiv.cpp)
  endif(ARGOS_COMPILE_QTOPENGL)
endif(ARGOS_BUILD_FOR_SIMULATOR)

#
# Create kheperaiv plugin
#
add_library(argos3plugin_${ARGOS_BUILD_FOR}_kheperaiv SHARED ${ARGOS3_SOURCES_PLUGINS_ROBOTS_KHEPERAIV})
target_link_libraries(argos3plugin_${ARGOS_BUILD_FOR}_kheperaiv
  argos3plugin_${ARGOS_BUILD_FOR}_genericrobot
  argos3plugin_${ARGOS_BUILD_FOR}_dynamics2d)
if(ARGOS_COMPILE_QTOPENGL)
  target_link_libraries(argos3plugin_${ARGOS_BUILD_FOR}_kheperaiv argos3plugin_${ARGOS_BUILD_FOR}_qtopengl)
endif(ARGOS_COMPILE_QTOPENGL)

#
# Installation
#
install(FILES ${ARGOS3_HEADERS_PLUGINS_ROBOTS_KHEPERAIV_CONTROLINTERFACE} DESTINATION include/argos3/plugins/robots/kheperaiv/control_interface)

if(ARGOS_BUILD_FOR_SIMULATOR)
  install(FILES ${ARGOS3_HEADERS_PLUGINS_ROBOTS_KHEPERAIV_SIMULATOR} DESTINATION include/argos3/plugins/robots/kheperaiv/simulator)
  install(FILES simulator/kheperaiv_texture_bottom.png simulator/kheperaiv_texture_side.png simulator/kheperaiv_texture_top.png DESTINATION include/argos3/plugins/simulator/visualizations/qt-opengl/textures)
endif(ARGOS_BUILD_FOR_SIMULATOR)

install(TARGETS argos3plugin_${ARGOS_BUILD_FOR}_kheperaiv
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib/argos3
  ARCHIVE DESTINATION lib/argos3)
