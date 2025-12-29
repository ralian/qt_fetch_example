qt_add_executable(example_2
    main.cpp
    rhiwindow.cpp
    rhiwindow.h
    rhiwindow.qrc
)
target_link_libraries(example_2 PRIVATE Qt6::GuiPrivate)
set_target_properties(example_2 PROPERTIES
  AUTOMOC ON
  AUTOMOC_EXECUTABLE ${Qt6_MOC_EXECUTABLE}
  AUTORCC ON
  AUTORCC_EXECUTABLE ${Qt6_RCC_EXECUTABLE}
)
