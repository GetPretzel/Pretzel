add_subdirectory(framework)

set(SOURCES ${SOURCES}
    main.cpp
    ui/register/register.cpp
)

# TODO: Add these resources in their respective resource files
set(RESOURCES ${RESOURCES}
    ui/ui.qrc
    framework/uicomponents/uicomponents.qrc
)

add_executable(Pretzel
    ${SOURCES}
    ${RESOURCES}
)

target_link_libraries(Pretzel PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Quick
    Qt5::Sql
    KDAB::kddockwidgets
    Actions
    # UiComponents
)
