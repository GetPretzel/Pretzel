set(UI_COMPONENTS_SOURCES
)

set(UI_COMPONENTS_RESOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/uicomponents.qrc
)

add_library(UiComponents STATIC
    # ${UI_COMPONENTS_SOURCES}
    ${UI_COMPONENTS_RESOURCES}
)

target_link_libraries(UiComponents
    Qt5::Core
    Qt5::Gui
    Qt5::Quick
)
