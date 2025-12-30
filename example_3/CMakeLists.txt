qt_add_executable(example_3
    main.cpp
    mainwindow.cpp
    mainwindow.h
)
add_dependencies(example_3 ${Qt6_PLATFORM_PLUGIN})
target_link_libraries(example_3 PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)
set_target_properties(example_3 PROPERTIES
  AUTOMOC ON
  AUTOMOC_EXECUTABLE ${Qt6_MOC_EXECUTABLE}
)
