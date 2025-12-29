add_executable(example_1 main.cpp rasterwindow.h)

add_dependencies(example_1 ${Qt6_PLATFORM_PLUGIN})
target_link_libraries(example_1 PRIVATE Qt6::Gui)

set_target_properties(example_1 PROPERTIES
  AUTOMOC ON
  AUTOMOC_EXECUTABLE ${Qt6_MOC_EXECUTABLE}
)
